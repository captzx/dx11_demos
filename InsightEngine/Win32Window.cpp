#include "PCH.h"
#include "Win32Window.h"

using namespace insight;

LRESULT CALLBACK InternalWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	LONG_PTR WindowProcPtr = GetWindowLongPtr(hwnd, 0);

	if (WindowProcPtr == 0) {
		return(DefWindowProc(hwnd, msg, wparam, lparam));
	}
	else {
		return(((IWindowProc*)WindowProcPtr)->WindowProc(hwnd, msg, wparam, lparam));
	}
}

Win32Window::Win32Window(){

}

Win32Window::~Win32Window(){
	Shutdown();
}

void Win32Window::Initialize(IWindowProc* MsgProc){
	WNDCLASSEX wc;

	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = InternalWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = sizeof(MsgProc);
	wc.hInstance = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"Win32Window";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (MsgProc != nullptr) {
		MsgProc->BeforeRegisterWindowClass(wc);
	}

	RegisterClassEx(&wc);

	RECT rc;
	rc.top = rc.left = 0;
	rc.right = _width;
	rc.bottom = _height;

	AdjustWindowRectEx(&rc, _style, false, 0);

	long adjust_width = rc.right - rc.left;
	long adjust_height = rc.bottom - rc.top;

	_hWnd = CreateWindowEx(
		NULL,
		wc.lpszClassName,
		_caption.c_str(),
		_style,
		_left,
		_top,
		adjust_width, adjust_height,
		NULL,
		NULL,
		NULL,
		NULL);

	RECT rect;
	GetClientRect(_hWnd, &rect);
	_width = rect.right - rect.left;
	_height = rect.bottom - rect.top;

	if (_hWnd) {
		// Set in the "extra" bytes the pointer to the IWindowProc object
		// which handles messages for the window
		SetWindowLongPtr(_hWnd, 0, (LONG_PTR)MsgProc);

		ShowWindow(_hWnd, SW_SHOWNORMAL);
		UpdateWindow(_hWnd);
	}
}

void Win32Window::Shutdown(){
	if (_hWnd)
		DestroyWindow(_hWnd);

	_hWnd = 0;
}

void Win32Window::Paint(){

}

POINT Win32Window::GetCursorPosition(){
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(_hWnd, &p);

	return p;
}