#include "pch.h"
#include "Application.h"
#include "Scene.h"
#include "Timer.h"

using namespace insight;

Application* Application::_spApplication = nullptr;

Application::Application() {
	_spApplication = this;

	_pScene = new Scene();
	_pTimer = new Timer();

}

Application::~Application() {
	SAFE_DELETE(_pScene);
	SAFE_DELETE(_pTimer);
}

Application* Application::GetApplication() {
	return _spApplication;
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

void Application::RequestTerimation() {
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
			PostQuitMessage(0);			//告诉操作系统一个线程退出请求 并发送一个WM_QUIT消息 参数为退出代码作为wParam传给WM_QUIT
			return 0;
			break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);//调用默认的窗口过程函数
}

void Application::BeforeRegisterWindowClass(WNDCLASSEX &wc) {

}