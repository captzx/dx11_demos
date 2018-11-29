#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "Renderer.h"
#include "RenderingPipeline.h"

using namespace insight;

Application* Application::spApplication = nullptr;

Application::Application() {
	spApplication = this;
}

Application::~Application() {

}

Application* Application::Get() {
	return spApplication;
}

bool Application::ConfigureEngineComponent() {
	_pWindow = new Window();
	_pWindow->Initialize(this);

	_pRenderer = new Renderer();
	_pRenderer->Initialize(D3D_DRIVER_TYPE_HARDWARE, D3D_FEATURE_LEVEL_11_0);

	_pRenderer->CreateSwapChain(_pWindow->GetHandle());

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

void Application::ShutdownEngineComponent() {
	SAFE_DELETE(_pWindow);
	SAFE_DELETE(_pRenderer);
}

void Application::Initialize() {

}

void Application::Update() {
	_pRenderer->Present();
}

void Application::Shutdown() {

}

void Application::MessageLoop() {
	MSG msg;

	while (true) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				return;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Update();
	}
}

void Application::RequestTermination() {
	PostQuitMessage(0);
}

LRESULT Application::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
		case WM_PRINT:
		case WM_KEYDOWN:
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MOUSEMOVE:
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}