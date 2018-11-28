#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "Renderer.h"

using namespace insight;

Application* Application::spApplication = nullptr;

Application::Application() {
	spApplication = this;

	_pWindow = new Window();
	_pWindow->Initialize(this);

	_pRenderer = new Renderer();
	_pRenderer->Initialize(D3D_DRIVER_TYPE_HARDWARE, D3D_FEATURE_LEVEL_11_0);

	_pRenderer->CreateSwapChain(GetHandle());
	_pRenderer->CreateRenderTargetView();
	_pRenderer->CreateDepthStencilView();
	_pRenderer->Extra();

}

Application::~Application() {

}

Application* Application::Get() {
	return spApplication;
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


HWND& Application::GetHandle() {
	return _pWindow->GetHandle();
}

void Application::Update() {
	_pRenderer->Present();
}