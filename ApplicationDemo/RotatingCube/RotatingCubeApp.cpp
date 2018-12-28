#include "pch.h"
#include "RotatingCubeApp.h"

#include "Window.h"
#include "Renderer.h"
#include "RenderingPipeline.h"
#include "SwapChain.h"

#include "RenderEffect.h"

#include "PipeBufferDesc.h"
#include "PipeTextureDesc.h"
#include "PipeBuffer.h"

using namespace insight;

RotatingCubeApp RotatingCubeInstance;

struct Vertex {
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};
bool RotatingCubeApp::ConfigureEngineComponent(){
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
	_pEffect->SetVertexShader(_pRenderer->LoadShader(VERTEX_SHADER, L"..//CommonData//Shaders//Cube.hlsl", "VS","vs_5_0"));
	_pEffect->SetPixelShader(_pRenderer->LoadShader(PIXEL_SHADER, L"..//CommonData//Shaders//Cube.hlsl", "PS", "ps_5_0"));

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
void RotatingCubeApp::ShutdownEngineComponent() {
	SAFE_DELETE(_pWindow);
	SAFE_DELETE(_pRenderer);
}

void RotatingCubeApp::Initialize() {
	_pWindow->SetCaption(GetName());

	{
		Vertex vertices[] =
		{
			{XMFLOAT3(-0.5f, 0.5f, 0.1f),	XMFLOAT4(Colors::Beige)},
			{XMFLOAT3(0.5f, 0.5f,0.1f),	XMFLOAT4(Colors::Beige) },
			{XMFLOAT3(0.5f, 0.5f, 0.5f),	XMFLOAT4(Colors::Beige) },
			{XMFLOAT3(-0.5f, 0.5f, 0.5f),	XMFLOAT4(Colors::Beige) },
			{XMFLOAT3(-0.5f, -0.5f, 0.1f), XMFLOAT4(Colors::Beige) },
			{XMFLOAT3(0.5f, -0.5f, 0.1f),	XMFLOAT4(Colors::Beige) },
			{XMFLOAT3(0.5f, -0.5f, 0.5f),	XMFLOAT4(Colors::Beige) },
			{XMFLOAT3(-0.5f, -0.5f, 0.5f),	XMFLOAT4(Colors::Beige) },
		};
		D3D11_SUBRESOURCE_DATA vd;
		vd.pSysMem = vertices;

		PipeBufferDesc vbd;
		vbd.SetAsVertexBuffer(8 * sizeof(Vertex));
		_pVertexBuffer = _pRenderer->CreateVertexBuffer(&vbd, &vd);

		UINT indices[] =
		{
			3,1,0,
			2,1,3,

			0,5,4,
			1,5,0,

			3,4,7,
			0,4,3,

			1,6,5,
			2,6,1,

			2,7,6,
			3,7,2,

			6,4,5,
			7,4,6,
		};
		D3D11_SUBRESOURCE_DATA id;
		id.pSysMem = indices;

		PipeBufferDesc ibd;
		ibd.SetAsIndexBuffer(sizeof(UINT) * 36, false);
		_pIndexBuffer = _pRenderer->CreateIndexBuffer(&ibd, &id);
	}

	auto world = XMMatrixIdentity();

	XMVECTOR Eye = XMVectorSet(0.0f, 0.0f, -10.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 0.5f, 0.0f, 0.0f);
	auto view = XMMatrixLookAtLH(Eye, At, Up);

	auto proj = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)_pWindow->GetWidth() / (FLOAT)_pWindow->GetHeight(), 0.01f, 10000.0f));
}
void RotatingCubeApp::Update() {
	_pRenderer->GetPipeline()->ClearColorBuffers(Colors::AliceBlue);
	_pRenderer->GetPipeline()->ClearDepthStencilBuffers();

	UINT stride = sizeof(Vertex);
	_pRenderer->GetPipeline()->Draw(_pEffect, _pVertexBuffer, _pIndexBuffer, _iVertexLayout, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, stride, 36);
	_pRenderer->Present(_pWindow->GetHandle(), _pWindow->GetSwapChain());
}
void RotatingCubeApp::Shutdown() {
}


std::wstring RotatingCubeApp::GetName() {
	return std::wstring(L"Rotating Cube Application");
}