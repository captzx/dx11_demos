#include "pch.h"
#include "EmptyApp.h"

#include "Window.h"
#include "Renderer.h"
#include "RenderingPipeline.h"
#include "SwapChain.h"

using namespace insight;

EmptyApp AppInstance;

void EmptyApp::Initialize() {
	_pWindow->SetCaption(GetName());
}

bool EmptyApp::ConfigureEngineComponent() {
	_pWindow = new Window();
	_pWindow->Initialize(this);

	_pRenderer = new Renderer();
	_pRenderer->Initialize(D3D_DRIVER_TYPE_HARDWARE, D3D_FEATURE_LEVEL_11_0);

	SwapChainDesc SCDesc;
	SCDesc.SetOutputWindow(_pWindow->GetHandle());
	SCDesc.SetHeight(_pWindow->GetHeight());
	SCDesc.SetWidth(_pWindow->GetWidth());
	_pRenderer->CreateSwapChain(SCDesc);

	ID3D11RenderTargetView* pRenderTargetView = _pRenderer->GetRenderTargetView();
	ID3D11DepthStencilView* pDepthStencilView = _pRenderer->GetDepthStencilView();

	_pRenderer->GetPipeline()->ClearRenderTargetView(pRenderTargetView, Colors::AliceBlue);
	_pRenderer->GetPipeline()->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);

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
void EmptyApp::ShutdownEngineComponent() {
	SAFE_DELETE(_pWindow);
	SAFE_DELETE(_pRenderer);
}
void EmptyApp::Update() {
	_pRenderer->Present();
}
void EmptyApp::Shutdown() {
}

std::wstring EmptyApp::GetName() {
	return std::wstring(L"EmptyApp Demo");
}
