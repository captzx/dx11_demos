#include "pch.h"
#include "RotatingCubeApp.h"

#include "Window.h"
#include "Renderer.h"
#include "RenderingPipeline.h"
#include "SwapChain.h"
#include "Shader.h"
#include "RenderEffect.h"

using namespace insight;

RotatingCubeApp RotatingCubeInstance;

bool RotatingCubeApp::ConfigureEngineComponent(){
	_pWindow = new Window();
	_pWindow->Initialize(this);

	_pRenderer = new Renderer();
	_pRenderer->Initialize(D3D_DRIVER_TYPE_HARDWARE, D3D_FEATURE_LEVEL_11_0);

	SwapChainDesc SCDesc;
	SCDesc.SetOutputWindow(_pWindow->GetHandle());
	SCDesc.SetHeight(_pWindow->GetHeight());
	SCDesc.SetWidth(_pWindow->GetWidth());
	_pRenderer->CreateSwapChain(SCDesc);

	_pEffect = new RenderEffect();

	_pEffect->SetVertexShader(_pRenderer->LoadShader(VERTEX_SHADER, L"RotatingCube_Shader.hlsl", "VSEntry","vs_5_0"));
	_pEffect->SetVertexShader(_pRenderer->LoadShader(PIXEL_SHADER, L"RotatingCube_Shader.hlsl", "PSEntry", "vs_5_0"));

	pRenderTargetView = _pRenderer->GetRenderTargetView();
	pDepthStencilView = _pRenderer->GetDepthStencilView();

	_pRenderer->GetShader(_pEffect->GetVertexShader());

	_pRenderer->GetPipeline()->ClearRenderTargetView(pRenderTargetView, Colors::AliceBlue);
	_pRenderer->GetPipeline()->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);

	D3D11_INPUT_ELEMENT_DESC desc[] ={
		{ "SV_POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
	layout.push_back(desc[0]);
	layout.push_back(desc[1]);
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

	_pRenderer->GetPipeline()->RSSetViewports(1, &viewport);

	return true;
}
void RotatingCubeApp::ShutdownEngineComponent() {
	SAFE_DELETE(_pWindow);
	SAFE_DELETE(_pRenderer);
}

struct Vertex{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};
void RotatingCubeApp::Initialize() {
	_pWindow->SetCaption(GetName());

	{
		Vertex vertices[] =
		{
			{XMFLOAT3(-1.0f, 1.0f, -1.0f),	XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
			{XMFLOAT3(1.0f, 1.0f, -1.0f),	XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
			{XMFLOAT3(1.0f, 1.0f, 1.0f),	XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
			{XMFLOAT3(-1.0f, 1.0f, 1.0f),	XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
			{XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
			{XMFLOAT3(1.0f, -1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
			{XMFLOAT3(1.0f, -1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{XMFLOAT3(-1.0f, -1.0f, 1.0f),	XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
		};
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = vertices;
		data.SysMemPitch = 0;
		data.SysMemSlicePitch = 0;

		BufferConfig vbConfig;
		vbConfig.SetDefaultVertexBuffer(8 * sizeof(Vertex), false);
		_pVertexBuffer = _pRenderer->CreateVertexBuffer(&vbConfig, &data);
		if (_pVertexBuffer->_iResource == -1) {
			assert(false);
		}
	}

	// create the index buffer resource (this is usually done by Geometry)
	{
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

		BufferConfig vbConfig;
		vbConfig.SetDefaultIndexBuffer(sizeof(UINT) * 36, false);
		_pIndexBuffer = _pRenderer->CreateIndexBuffer(&vbConfig, &data);
		if (_pIndexBuffer->_iResource == -1) {
			assert(false);
		}
	}

	// Setup the "camera"
	XMStoreFloat4x4(&_worldMatrix, XMMatrixIdentity());


	XMVECTOR Eye = XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMStoreFloat4x4(&_viewMatrix, XMMatrixLookAtLH(Eye, At, Up));

	XMStoreFloat4x4(&_projMatrix, XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)_pWindow->GetWidth() / (FLOAT)_pWindow->GetHeight(), 0.01f, 100.0f));
}
void RotatingCubeApp::Update() {

	_pRenderer->pImmPipeline->ClearBuffers(Vector4f(0.0f, 0.0f, 0.0f, 0.0f), 1.0f);

	// Update the object position in worldspace

	static DWORD dwTimeStart = 0;
	static float t = 0.0f;
	DWORD dwTimeCur = GetTickCount();
	if (dwTimeStart == 0)
		dwTimeStart = dwTimeCur;
	t = (dwTimeCur - dwTimeStart) / 1000.0f;

	_worldMatrix = Matrix4f::RotationMatrixY(t) * Matrix4f::RotationMatrixX(t);

	_pRenderer->_pParamMgr->SetWorldMatrixParameter(&_worldMatrix);

	// Perform the actual drawing

	UINT stride = sizeof(Vertex);
	_pRenderer->pImmPipeline->Draw(_Effect, _pVertexBuffer, _pIndexBuffer,
		_VertexLayout, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, stride, 36, _pRenderer->_pParamMgr);

	// Present the results

	_pRenderer->Present(_pWindow->GetHandle(), _pWindow->GetSwapChain());
}
void RotatingCubeApp::Shutdown() {
}


std::wstring RotatingCubeApp::GetName() {
	return std::wstring(L"Rotating Cube Application");
}