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

#include "PipeBuffer.h"
#include "ParameterManager.h"
#include "RenderParameter.h"
#include "ShaderReflection.h"

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
void RenderingPipeline::BindConstantBufferParameter(ShaderType type, RenderParameter* pParameter, UINT slot, IParameterManager* pParamManager) {
	Renderer* pRenderer = Renderer::Get();
	unsigned int threadID = pParamManager->GetID();

	if (pParameter) {
		if (pParameter->GetParameterType() == CBUFFER) {
			ConstantBufferParameter* pConstantBufferParameter = reinterpret_cast<ConstantBufferParameter*>(pParameter);
			int resrouceIndex = pConstantBufferParameter->GetResourceIndex(threadID);

			PipeResource* pResource = pRenderer->GetResourceByIndex(resrouceIndex);

			if (pResource || (resrouceIndex == -1)) {
				ID3D11Buffer* pBuffer = 0;

				if (resrouceIndex >= 0) {
					pBuffer = (ID3D11Buffer*)pResource->GetResource();
				}

				ProgrammableStage[type]->DesiredState.ConstantBuffers.Set(slot, pBuffer);
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

void RenderingPipeline::Draw(RenderEffect* effect, std::shared_ptr<PipeResourceProxy> vb, std::shared_ptr<PipeResourceProxy> ib,
	int inputLayout, D3D11_PRIMITIVE_TOPOLOGY primType,
	UINT vertexStride, UINT numIndices, IParameterManager* pParameterManager)
{
	InputAssemblerStage.ClearDesiredState();

	InputAssemblerStage.DesiredState.PrimitiveTopology.Set(primType);

	if (vb != NULL) {
		InputAssemblerStage.DesiredState.VertexBuffers.Set(0, vb->_iResource);
		InputAssemblerStage.DesiredState.VertexBufferStrides.Set(0, vertexStride);
		InputAssemblerStage.DesiredState.VertexBufferOffsets.Set(0, 0);
	}

	if (ib != NULL) {
		InputAssemblerStage.DesiredState.IndexBuffer.Set(ib->_iResource);
		InputAssemblerStage.DesiredState.IndexBufferFormat.Set(DXGI_FORMAT_R32_UINT);
	}

	if (vb != NULL) {
		InputAssemblerStage.DesiredState.InputLayout.Set(inputLayout);
	}

	InputAssemblerStage.ApplyDesiredState(_pDeviceContext.Get());

	ClearPipelineResources();
	effect->ConfigurePipeline(this, pParameterManager);
	ApplyPipelineResources();

	_pDeviceContext->DrawIndexed(numIndices, 0, 0);
}


void RenderingPipeline::UpdateSubresource(ConstantBuffer* cBuffer, void* pData) {
	_pDeviceContext->UpdateSubresource(cBuffer->GetResource(), 0, nullptr, &pData, 0, 0);
}

D3D11_MAPPED_SUBRESOURCE RenderingPipeline::MapResource(PipeResource * pPipeResource, UINT subresource, D3D11_MAP actions, UINT flags){
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	mappedSubresource.pData = NULL;
	mappedSubresource.DepthPitch = mappedSubresource.RowPitch = 0;

	if (!pPipeResource) {
		return mappedSubresource;
	}

	ID3D11Resource* pResource = pPipeResource->GetResource();

	if (!pResource) {
		return mappedSubresource;
	}

	HRESULT hr = _pDeviceContext->Map(pResource, subresource, actions, flags, &mappedSubresource);
	
	if (FAILED(hr)) {
		// ... 
	}
	
	return mappedSubresource;
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

void RenderingPipeline::BindShader(ShaderType type, int ID, IParameterManager* pParameterManager){
	Renderer* pRenderer = Renderer::Get();
	Shader* pShader = pRenderer->GetShader(ID);

	ProgrammableStage[type]->DesiredState.ShaderProgram.Set(ID);

	if (pShader){
		if (pShader->GetType() == type){
			pShader->GetReflection()->BindParameters(type, this, pParameterManager);
		}
		else{

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

