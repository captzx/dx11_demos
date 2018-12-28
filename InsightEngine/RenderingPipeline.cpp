#include "pch.h"
#include "RenderingPipeline.h"
#include "Application.h"
#include "Renderer.h"

#include "RenderEffect.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "PipeView.h"
#include "PipeResource.h"
#include "ParameterManager.h"

using namespace insight;

RenderingPipeline::RenderingPipeline() {
	ProgrammableStage[VERTEX_SHADER] = &VertexShaderStage;
	ProgrammableStage[PIXEL_SHADER] = &PixelShaderStage;
}

RenderingPipeline::~RenderingPipeline() {

}

void RenderingPipeline::SetDeviceContext(ID3D11DeviceContext* pDeviceContext) {
	_pDeviceContext = pDeviceContext;
}
//
//void RenderingPipeline::UpdateSubresource(ID3D11Buffer* cb, ConstantBuffer* cBuffer) {
//	_pDeviceContext->UpdateSubresource(cb, 0, nullptr, cBuffer, 0, 0);
//}

void RenderingPipeline::ClearColorBuffers(const FLOAT ColorRGBA[4]) {
	ID3D11RenderTargetView* pRenderTargetViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { NULL };

	// Our output merger class manages the current render targets bound to the pipeline.
	// The number of views that are currently set refers to the views that the application
	// has submitted to the pipeline, but not necessarily that have been bound to the API.
	// For each view that the application thinks is bound, we clear it as requested.  Since
	// the view count is the number of non-null views, we don't need to check here.

	UINT viewCount = OutputMergerStage.GetCurrentState().GetRenderTargetCount();

	for (UINT i = 0; i < viewCount; ++i)
	{
		int rtv = OutputMergerStage.GetCurrentState().RenderTargetViews.Get(i);
		RenderTargetView& RTV = Renderer::Get()->GetRenderTargetViewByIndex(rtv);
		pRenderTargetViews[i] = RTV.Get();
		if (pRenderTargetViews[i] != nullptr) {
			_pDeviceContext->ClearRenderTargetView(pRenderTargetViews[i], ColorRGBA);
		}
	}
}

void RenderingPipeline::ClearDepthStencilBuffers(float depth, UINT stencil) {
	ID3D11DepthStencilView* pDepthStencilView = 0;

	// Check if the output merger currently has a depth target set, and if so clear it.

	if (OutputMergerStage.GetCurrentState().DepthTargetViews.Get() != -1)
	{
		int dsv = OutputMergerStage.GetCurrentState().DepthTargetViews.Get();
		DepthStencilView DSV = Renderer::Get()->GetDepthStencilViewByIndex(dsv);
		pDepthStencilView = DSV.Get();
		if (pDepthStencilView != nullptr) {
			_pDeviceContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, depth, stencil);
		}
	}
}
void RenderingPipeline::BindConstantBufferParameter(ShaderType type, RenderParameter* pParam, UINT slot, IParameterManager* pParamManager) {
	Renderer* pRenderer = Renderer::Get();

	unsigned int tID = pParamManager->GetID();

	if (pParam != 0) {

		// Check the type of the parameter
		if (pParam->GetParameterType() == CBUFFER) {
			ConstantBufferParameter* pBuffer = reinterpret_cast<ConstantBufferParameter*>(pParam);
			int ID = pBuffer->GetIndex(tID);

			PipeResource* pResource = pRenderer->GetResourceByIndex(ID);

			// Allow a range including -1 up to the number of resources
			if (pResource || (ID == -1)) {
				// Get the resource to be set, and pass it in to the desired shader type

				ID3D11Buffer* pBuffer = 0;

				if (ID >= 0) {
					pBuffer = (ID3D11Buffer*)pResource->GetResource();
				}

				//ShaderStages[type]->DesiredState.ConstantBuffers.SetState(slot, pBuffer);
			}
			else {
				//Log::Get().Write(L"Tried to set an invalid constant buffer ID!");
			}
		}
		else {
			//Log::Get().Write(L"Tried to set a non-constant buffer ID as a constant buffer!");
		}
	}
	else {
		//Log::Get().Write(L"Tried to set a non-existing parameter as a constant buffer!");
	}
}

void RenderingPipeline::Draw(RenderEffect* effect, ResourcePtr vb, ResourcePtr ib,
	int inputLayout, D3D11_PRIMITIVE_TOPOLOGY primType,
	UINT vertexStride, UINT numIndices)
{
	InputAssemblerStage.ClearDesiredState();

	// Configure the pipeline input data with the input assembler
	// state object.

	InputAssemblerStage.DesiredState.PrimitiveTopology.Set(primType);

	// Bind the vertex and index buffers.
	if (vb != NULL) {
		InputAssemblerStage.DesiredState.VertexBuffers.Set(0, vb->_iResource);
		InputAssemblerStage.DesiredState.VertexBufferStrides.Set(0, vertexStride);
		InputAssemblerStage.DesiredState.VertexBufferOffsets.Set(0, 0);
	}

	if (ib != NULL) {
		InputAssemblerStage.DesiredState.IndexBuffer.Set(ib->_iResource);
		InputAssemblerStage.DesiredState.IndexBufferFormat.Set(DXGI_FORMAT_R32_UINT);
	}

	// Bind the input layout.
	if (vb != NULL) {
		InputAssemblerStage.DesiredState.InputLayout.Set(inputLayout);
	}

	// Set and apply the state in this pipeline manager's input assembler.
	InputAssemblerStage.ApplyDesiredState(_pDeviceContext.Get());

	// Use the effect to load all of the pipeline stages here.
	ClearPipelineResources();
	effect->ConfigurePipeline(this);
	ApplyPipelineResources();

	_pDeviceContext->DrawIndexed(numIndices, 0, 0);
}

D3D11_MAPPED_SUBRESOURCE RenderingPipeline::MapResource(PipeResource * pPipeResource, UINT subresource, D3D11_MAP actions, UINT flags){
	D3D11_MAPPED_SUBRESOURCE msr;
	msr.pData = nullptr;
	msr.DepthPitch = 0;
	msr.RowPitch = 0;

	if (pPipeResource) {
		ID3D11Resource* pResource = nullptr;
		pResource = pPipeResource->GetResource();

		if (pResource) {
			HRESULT hr = _pDeviceContext->Map(pResource, subresource, actions, flags, &msr);

			if (FAILED(hr)) {
				
			}
		}
	}
	
	return msr;
}

void RenderingPipeline::UnMapResource(PipeResource * pPipeResource, UINT subresource){
	if (pPipeResource) {
		ID3D11Resource* pResource = nullptr;
		pResource = pPipeResource->GetResource();

		if (pResource) {
			_pDeviceContext->Unmap(pResource, subresource);
		}
	}
}

void RenderingPipeline::BindShader(ShaderType type, int ID){
	Renderer* pRenderer = Renderer::Get();
	Shader* pShader = pRenderer->GetShader(ID);

	// Record the shader ID for use later on
	ProgrammableStage[type]->DesiredState.ShaderProgram.Set(ID);

	// Check if the shader has a valid identifier
	if (pShader){
		// Perform the actual binding to the pipeline, and then bind all needed
		// parameters.

		if (pShader->GetType() == type){
			// Before binding the shader, have it update its required parameters.  These
			// parameters will then be bound to the pipeline after the shader is bound.

			//pShader->GetReflection()->BindParameters(type, this, pParamManager);
		}
		else{
			//Log::Get().Write(L"Tried to set the wrong type of shader ID!");
		}
	}
}

void RenderingPipeline::ClearPipelineResources(){
	VertexShaderStage.ClearDesiredState();
	PixelShaderStage.ClearDesiredState();
}

void RenderingPipeline::ApplyPipelineResources(){
	VertexShaderStage.ApplyDesiredState(_pDeviceContext.Get());
	PixelShaderStage.ApplyDesiredState(_pDeviceContext.Get());
	RasterizerStage.ApplyDesiredState(_pDeviceContext.Get());
	OutputMergerStage.ApplyDesiredBlendAndDepthStencilStates(_pDeviceContext.Get());
}

void RenderingPipeline::ApplyRenderTargets(){
	OutputMergerStage.ApplyDesiredRenderTargetStates(_pDeviceContext.Get());
}

