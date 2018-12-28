#include "pch.h"
#include "EmptyApp.h"

#include "Window.h"
#include "Renderer.h"
#include "RenderingPipeline.h"
#include "SwapChain.h"

#include "RenderEffect.h"

#include "PipeBufferDesc.h"
#include "PipeTextureDesc.h"
#include "PipeBuffer.h"

using namespace insight;

EmptyApp AppInstance;


void EmptyApp::Initialize() {
	_pWindow->SetCaption(GetName());

	{
		Vertex vertices[] =
		{
			{ XMFLOAT3(0.0f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) }
		};
		D3D11_SUBRESOURCE_DATA vd;
		vd.pSysMem = vertices;

		PipeBufferDesc vbd;
		vbd.SetAsVertexBuffer(3 * sizeof(Vertex));
		_pVertexBuffer = _pRenderer->CreateVertexBuffer(&vbd, &vd);
	}

	{

		UINT indices[] =
		{
			0,1,2
		};
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = indices;
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;

		PipeBufferDesc ibd;
		ibd.SetAsIndexBuffer(sizeof(UINT) * 3, false);
		_pIndexBuffer = _pRenderer->CreateIndexBuffer(&ibd, &data);
	}
}

bool EmptyApp::ConfigureEngineComponent() {
	int height = 600;
	int width = 800;

	_pWindow = new Window();
	_pWindow->Initialize(this);
	_pWindow->SetWidth(width);
	_pWindow->SetHeight(height);

	_pRenderer = new Renderer();
	_pRenderer->Initialize(D3D_DRIVER_TYPE_HARDWARE, D3D_FEATURE_LEVEL_11_0);

	SwapChainDesc SCDesc;
	SCDesc.SetOutputWindow(_pWindow->GetHandle());
	SCDesc.SetHeight(height);
	SCDesc.SetWidth(width);
	_iSwapChain = _pRenderer->CreateSwapChain(SCDesc);
	_pWindow->SetSwapChain(_iSwapChain);

	_pRenderTargetView = _pRenderer->GetSwapChainResource(_iSwapChain);

	Texture2dDesc DepthDesc;
	DepthDesc.SetDepthBuffer(width, height);
	_pDepthStencilView = _pRenderer->CreateTexture2D(&DepthDesc, 0);


	_pRenderer->GetPipeline()->OutputMergerStage.ClearDesiredState();
	_pRenderer->GetPipeline()->OutputMergerStage.DesiredState.RenderTargetViews.Set(0, _pRenderTargetView->_iResourceRTV);
	_pRenderer->GetPipeline()->OutputMergerStage.DesiredState.DepthTargetViews.Set(_pDepthStencilView->_iResourceDSV);
	_pRenderer->GetPipeline()->ApplyRenderTargets();

	_pEffect = new RenderEffect();
	_pEffect->SetVertexShader(_pRenderer->LoadShader(VERTEX_SHADER, L"..//CommonData//Shaders//Triangle.hlsl", "VS", "vs_5_0"));
	_pEffect->SetPixelShader(_pRenderer->LoadShader(PIXEL_SHADER, L"..//CommonData//Shaders//Triangle.hlsl", "PS", "ps_5_0"));

	D3D11_INPUT_ELEMENT_DESC vertexDesc[] ={
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
	layout.push_back(vertexDesc[0]);
	layout.push_back(vertexDesc[1]);
	_iVertexLayout = _pRenderer->CreateInputLayout(layout, _pEffect->GetVertexShader());
	if (_iVertexLayout == -1) {
		assert(false);
	}

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(800);
	viewport.Height = static_cast<float>(600);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	int ViewPort = _pRenderer->CreateViewPort(viewport);
	_pRenderer->GetPipeline()->RasterizerStage.DesiredState.ViewportCount.Set(1);
	_pRenderer->GetPipeline()->RasterizerStage.DesiredState.Viewports.Set(0, ViewPort);

	return true;
}
void EmptyApp::ShutdownEngineComponent() {
	SAFE_DELETE(_pWindow);
	SAFE_DELETE(_pRenderer);
	SAFE_DELETE(_pEffect);
}
void EmptyApp::Update() {
	_pRenderer->GetPipeline()->ClearColorBuffers(Colors::AliceBlue);
	_pRenderer->GetPipeline()->ClearDepthStencilBuffers();
	
	UINT stride = sizeof(Vertex);
	_pRenderer->GetPipeline()->Draw(_pEffect, _pVertexBuffer, _pIndexBuffer,_iVertexLayout, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, stride, 3);
	_pRenderer->Present(_pWindow->GetHandle(), _pWindow->GetSwapChain());
}
void EmptyApp::Shutdown() {
}

std::wstring EmptyApp::GetName() {
	return std::wstring(L"EmptyApp Demo");
}
