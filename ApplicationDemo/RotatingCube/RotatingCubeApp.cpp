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

#include "ParameterManager.h"
#include "Geometry.h"

using namespace insight;

RotatingCubeApp RotatingCubeInstance;

bool RotatingCubeApp::ConfigureEngineComponent(){
	int height = 600;
	int width = 800;

	_pWindow = new Window();
	_pWindow->Initialize(this);
	_pWindow->SetWidth(width);
	_pWindow->SetHeight(height);

	_pRenderer = new Renderer();
	_pRenderer->Initialize(D3D_DRIVER_TYPE_HARDWARE, D3D_FEATURE_LEVEL_11_0);

	SwapChainDesc swapChainDesc;
	swapChainDesc.SetOutputWindow(_pWindow->GetHandle());
	swapChainDesc.SetHeight(height);
	swapChainDesc.SetWidth(width);
	_iSwapChain = _pRenderer->CreateSwapChain(swapChainDesc);
	_pWindow->SetSwapChain(_iSwapChain);

	_pRenderTargetView = _pRenderer->GetSwapChainResource(_iSwapChain);

	Texture2dDesc depthStencilDesc;
	depthStencilDesc.SetDepthBuffer(width, height);
	_pDepthStencilView = _pRenderer->CreateTexture2D(&depthStencilDesc, 0);

	_pRenderer->GetPipeline()->OutputMergerStage.ClearDesiredState();
	_pRenderer->GetPipeline()->OutputMergerStage.DesiredState.RenderTargetViews.Set(0, _pRenderTargetView->_iResourceRTV);
	_pRenderer->GetPipeline()->OutputMergerStage.DesiredState.DepthTargetViews.Set(_pDepthStencilView->_iResourceDSV);
	_pRenderer->GetPipeline()->ApplyRenderTargets();

	_pEffect = new RenderEffect();
	_pEffect->SetVertexShader(_pRenderer->LoadShader(VERTEX_SHADER, L"..//CommonData//Shaders//RotatingCube.hlsl", "VS","vs_5_0"));
	_pEffect->SetPixelShader(_pRenderer->LoadShader(PIXEL_SHADER, L"..//CommonData//Shaders//RotatingCube.hlsl", "PS", "ps_5_0"));

	D3D11_INPUT_ELEMENT_DESC aInputElementDescs[] ={
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	std::vector<D3D11_INPUT_ELEMENT_DESC> vLayouts;
	vLayouts.push_back(aInputElementDescs[0]);
	vLayouts.push_back(aInputElementDescs[1]);
	_iVertexLayout = _pRenderer->CreateInputLayout(vLayouts, _pEffect->GetVertexShader());
	
	if (_iVertexLayout == -1) {
		assert(false);
	}

	D3D11_VIEWPORT viewPort;
	viewPort.Width = static_cast<float>(800);
	viewPort.Height = static_cast<float>(600);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;

	int iViewPort = _pRenderer->CreateViewPort(viewPort);
	_pRenderer->GetPipeline()->RasterizerStage.DesiredState.ViewportCount.Set(1);
	_pRenderer->GetPipeline()->RasterizerStage.DesiredState.Viewports.Set(0, iViewPort);

	return true;
}
void RotatingCubeApp::ShutdownEngineComponent() {
	SAFE_DELETE(_pWindow);
	SAFE_DELETE(_pRenderer);
}

void RotatingCubeApp::Initialize() {
	_pWindow->SetCaption(GetName());

	{
		Vertex_Pos_Color vertices[] = {
			{XMFLOAT3(-1.0f, -1.0f, -1.0f),	XMFLOAT4(Colors::Blue)},
			{XMFLOAT3(-1.0f, +1.0f, -1.0f),	XMFLOAT4(Colors::White) },
			{XMFLOAT3(+1.0f, +1.0f, -1.0f),	XMFLOAT4(Colors::Green) },
			{XMFLOAT3(+1.0f, -1.0f, -1.0f),	XMFLOAT4(Colors::Black) },
			{XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT4(Colors::Yellow) },
			{XMFLOAT3(-1.0f, +1.0f, +1.0f),	XMFLOAT4(Colors::Crimson) },
			{XMFLOAT3(+1.0f, +1.0f, +1.0f),	XMFLOAT4(Colors::BlanchedAlmond) },
			{XMFLOAT3(+1.0f, -1.0f, +1.0f),	XMFLOAT4(Colors::BlueViolet) },
		};
		D3D11_SUBRESOURCE_DATA vd;
		vd.pSysMem = vertices;

		PipeBufferDesc vbd;
		vbd.SetAsVertexBuffer(8 * sizeof(Vertex_Pos_Color));
		_pVertexBuffer = _pRenderer->CreateVertexBuffer(&vbd, &vd);

		UINT indices[] = {
			0, 1, 2,
			0, 2, 3,

			// back face
			4, 6, 5,
			4, 7, 6,

			// left face
			4, 5, 1,
			4, 1, 0,

			// right face
			3, 2, 6,
			3, 6, 7,

			// top face
			1, 5, 6,
			1, 6, 2,

			// bottom face
			4, 0, 3,
			4, 3, 7
		};
		D3D11_SUBRESOURCE_DATA id;
		id.pSysMem = indices;

		PipeBufferDesc ibd;
		ibd.SetAsIndexBuffer(sizeof(UINT) * 36, false);
		_pIndexBuffer = _pRenderer->CreateIndexBuffer(&ibd, &id);
	}

	XMStoreFloat4x4(&_f4x4World, XMMatrixIdentity());
	XMVECTOR pos = XMVectorSet(3.0f, 3.0f, -3.0f, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMStoreFloat4x4(&_f4x4View, XMMatrixTranspose(XMMatrixLookAtLH(pos, target, up)));
	XMStoreFloat4x4(&_f4x4Proj, XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600, 1.0f, 1000.0f)));

	_pRenderer->GetParameterManager()->SetWorldMatrixParameter(&_f4x4World);
	_pRenderer->GetParameterManager()->SetViewMatrixParameter(&_f4x4View);
	_pRenderer->GetParameterManager()->SetProjMatrixParameter(&_f4x4Proj);
}
void RotatingCubeApp::Update() {
	_pRenderer->GetPipeline()->ClearColorBuffers(Colors::AliceBlue);
	_pRenderer->GetPipeline()->ClearDepthStencilBuffers();

	_pRenderer->GetPipeline()->Draw(_pEffect, _pVertexBuffer, _pIndexBuffer, _iVertexLayout, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, sizeof(Vertex_Pos_Color), 36, _pRenderer->GetParameterManager());
	_pRenderer->Present(_pWindow->GetHandle(), _pWindow->GetSwapChain());
}
void RotatingCubeApp::Shutdown() {
}


std::wstring RotatingCubeApp::GetName() {
	return std::wstring(L"Rotating Cube Application");
}