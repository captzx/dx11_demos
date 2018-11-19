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
			PostQuitMessage(0);			//���߲���ϵͳһ���߳��˳����� ������һ��WM_QUIT��Ϣ ����Ϊ�˳�������ΪwParam����WM_QUIT
			return 0;
			break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);//����Ĭ�ϵĴ��ڹ��̺���
}

void Application::BeforeRegisterWindowClass(WNDCLASSEX &wc) {

}