#include "pch.h"
#include "RotatingCubeApp.h"
#include "Application.h"
#include "Win32Window.h"
#include "Renderer.h"
#include "SwapChainConfig.h"
#include "Texture2DConfig.h"
#include "PipelineManager.h"
#include "BufferConfig.h"


#include <glog/logging.h>

using namespace insight;

struct Vertex{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

RotatingCubeApp _RotatingCubeInstance;

RotatingCubeApp::RotatingCubeApp() {
	//LOG(INFO) << "info test" << "hello log!";  //输出一个Info日志
	//LOG(WARNING) << "warning test";  //输出一个Warning日志
	//LOG(ERROR) << "error test";  //输出一个Error日志
}

bool RotatingCubeApp::ConfigureEngineComponent() {
	_pWindow = new Win32Window();
	_pWindow->SetCaption(GetName());
	_pWindow->Initialize(this);

	_pRenderer = new Renderer();
	if (!_pRenderer->Initialize(D3D_DRIVER_TYPE_HARDWARE, D3D_FEATURE_LEVEL_11_0)) {
		LOG(ERROR) << "Could not create hardware device";
	}

	SwapChainConfig swapChainConfig;
	swapChainConfig.SetWidth(_pWindow->GetWidth());
	swapChainConfig.SetHeight(_pWindow->GetHeight());
	swapChainConfig.SetOutputWindow(_pWindow->GetHandle());
	_iSwapChain = _pRenderer->CreateSwapChain(&swapChainConfig);
	_pWindow->SetSwapChain(_iSwapChain);

	_pRenderTarget = _pRenderer->GetSwapChainResource(_iSwapChain);

	Texture2DConfig depthConfig;
	depthConfig.SetDepthBuffer(_pWindow->GetWidth(), _pWindow->GetHeight());
	_pDepthTarget = _pRenderer->CreateTexture2D(&depthConfig, 0);

	PipelineManager* pImmPipeline = _pRenderer->GetImmPipeline();
	pImmPipeline->ClearRenderTargets();
	pImmPipeline->OutputMergerStage.DesiredState.RenderTargetViews.SetState(0, _pRenderTarget->_iResourceRTV);
	pImmPipeline->OutputMergerStage.DesiredState.DepthTargetViews.SetState(_pDepthTarget->_iResourceDSV);
	pImmPipeline->ApplyRenderTargets();

	// create shader effect

	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{ "SV_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
	layout.push_back(desc[0]);
	layout.push_back(desc[1]);
	_iVertexLayout = _pRenderer->CreateInputLayout(layout, _pEffect>GetVertexShader());
	if (_iVertexLayout == -1) {
		LOG(ERROR) << "Failed to create vertex layout";
		assert(false);
	}

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(_pWindow->GetWidth());
	viewport.Height = static_cast<float>(_pWindow->GetHeight());
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	int ViewPort = _pRenderer->CreateViewPort(viewport);
	pImmPipeline->RasterizerStage.DesiredState.ViewportCount.SetState(1);
	pImmPipeline->RasterizerStage.DesiredState.Viewports.SetState(0, ViewPort);
	return(true);
}

void RotatingCubeApp::ShutdownEngineComponent() {
	if (_pRenderer) {
		_pRenderer->Shutdown();
		delete _pRenderer;
	}

	if (_pWindow) {
		_pWindow->Shutdown();
		delete _pWindow;
	}
}

void RotatingCubeApp::Initialize() {
	Vertex vertices[] =
	{
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
	};
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertices;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	BufferConfig vbConfig;
	vbConfig.SetDefaultVertexBuffer(8 * sizeof(Vertex), false);
	_pVertexBuffer = _pRenderer->CreateVertexBuffer(&vbConfig, &data);
	if (_pVertexBuffer->_iResource == -1) {
		LOG(ERROR)<<"Failed to create vertex buffer";
		assert(false);
	}

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
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = indices;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	BufferConfig ibConfig;
	ibConfig.SetDefaultIndexBuffer(sizeof(UINT) * 36, false);
	_pIndexBuffer = _pRenderer->CreateIndexBuffer(&ibConfig, &data);
	if (_pIndexBuffer->_iResource == -1) {
		LOG(ERROR) << "Failed to create index buffer";
		assert(false);
	}

	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&_mWorld, I);

	XMVECTOR eye = XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
	XMVECTOR at = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX V = XMMatrixLookAtLH(eye, at, up);
	XMStoreFloat4x4(&_mView, V);

	XMMATRIX P = XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)_pWindow->GetWidth() / (FLOAT)_pWindow->GetHeight(), 0.01f, 100.0f);
	XMStoreFloat4x4(&_mProj, P);


	_pRenderer->_pParamMgr->SetWorldMatrixParameter(&_mWorld);
	_pRenderer->_pParamMgr->SetViewMatrixParameter(&_mView);
	_pRenderer->_pParamMgr->SetProjMatrixParameter(&_mProj);
}

void RotatingCubeApp::Update() {
	_pRenderer->GetImmPipeline()->ClearBuffer(AliceBlue, 1.0f);

	// Update the object position in worldspace

	static DWORD dwTimeStart = 0;
	static float t = 0.0f;
	DWORD dwTimeCur = GetTickCount();
	if (dwTimeStart == 0)
		dwTimeStart = dwTimeCur;
	t = (dwTimeCur - dwTimeStart) / 1000.0f;

	// m_WorldMatrix = Matrix4f::RotationMatrixY(t) * Matrix4f::RotationMatrixX(t);

	_pRenderer->m_pParamMgr->SetWorldMatrixParameter(&_mWorld);

	// Perform the actual drawing

	UINT stride = sizeof(Vertex);
	_pRenderer->pImmPipeline->Draw(_Effect, _pVertexBuffer, _pIndexBuffer,
		_iVertexLayout, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, stride, 36, _pRenderer->_pParamMgr);

	// Present the results

	_pRenderer->Present(_pWindow->GetHandle(), _pWindow->GetSwapChain());
}

void RotatingCubeApp::Shutdown() {

}

std::wstring RotatingCubeApp::GetName() {
	return std::wstring(L"Rotating Cube Application");
}