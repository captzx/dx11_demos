#include "pch.h"
#include "Window.h"

#include "IWindowProc.h"

using namespace insight;

LRESULT CALLBACK InternalWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	LONG_PTR WindowProcPtr = GetWindowLongPtr(hwnd, 0);

	if (WindowProcPtr == 0) {
 		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	else {
		return ((IWindowProc*)WindowProcPtr)->WindowProc(hwnd, msg, wparam, lparam);
	}
}

Window::Window(){
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	_iLeft = (screenWidth - _iWidth) / 2;
	_iTop = (screenHeight - _iHeight) / 2;
}

Window::~Window(){
	Shutdown();
}

void Window::Initialize(IWindowProc* MsgProc) {
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
	wc.lpszClassName = L"Window";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (MsgProc != nullptr) {
		// MsgProc->BeforeRegisterWindowClass(wc);
	}

	RegisterClassEx(&wc);

	RECT rect;
	rect.top = rect.left = 0;
	rect.right = _iWidth;
	rect.bottom = _iHeight;

	AdjustWindowRectEx(&rect, _dwStyle, false, 0);
	long adjust_iWidth = rect.right - rect.left;
	long adjust_iHeight = rect.bottom - rect.top;

	_hWnd = CreateWindowEx(NULL, wc.lpszClassName, _wsCaption.c_str(), _dwStyle, 
		_iLeft, _iTop, adjust_iWidth, adjust_iHeight, NULL, NULL, NULL, NULL);

	GetClientRect(_hWnd, &rect);
	_iWidth = rect.right - rect.left;
	_iHeight = rect.bottom - rect.top;

	if (_hWnd) {
		SetWindowLongPtr(_hWnd, 0, (LONG_PTR)MsgProc);

		ShowWindow(_hWnd, SW_SHOWNORMAL);
		UpdateWindow(_hWnd);
	}
}

void Window::Shutdown() {
	if (_hWnd)
		DestroyWindow(_hWnd);

	_hWnd = 0;
}

POINT Window::GetCursorPosition() const {
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(_hWnd, &pos);

	return pos;
}

HWND Window::GetHandle() const{
	return _hWnd;
}

int Window::GetWidth() const {
	RECT rect;
	memset(&rect, 0, sizeof(rect));

	GetClientRect(_hWnd, &rect);

	return rect.right - rect.left;
}

int Window::GetHeight() const {
	RECT rect;
	memset(&rect, 0, sizeof(rect));

	GetClientRect(_hWnd, &rect);

	return rect.bottom - rect.top;
}

int Window::GetLeft() const {
	POINT point;
	memset(&point, 0, sizeof(point));

	ClientToScreen(_hWnd, &point);

	return point.x;
}

int Window::GetTop() const {
	POINT point;
	memset(&point, 0, sizeof(point));

	ClientToScreen(_hWnd, &point);

	return point.y;
}

std::wstring Window::GetCaption() const {
	return _wsCaption;
}

DWORD Window::GetStyle() const {
	return _dwStyle;
}

void Window::SetWidth(int width) {
	_iWidth = width;
	_UpdateWindowState();
}

void Window::SetHeight(int height) {
	_iHeight = height;
	_UpdateWindowState();
}

void Window::SetSize(int width, int height){
	_iWidth = width;
	_iHeight = height;

	_UpdateWindowState();
}

void Window::SetPosition(int left, int top){
	_iLeft = left;
	_iTop = top;

	_UpdateWindowState();
}

void Window::SetCaption(const std::wstring& caption) {
	_wsCaption = caption;

	if (_hWnd != 0) {
		SetWindowText(_hWnd, caption.c_str());
	}
}

void Window::ResizeWindow(int width, int height){
	_iWidth = width;
	_iHeight = height;

	_UpdateWindowState();
}

void Window::SetSwapChain(int swapchain){
	_iSwapChain = swapchain;
}

void Window::SetStyle(DWORD style){
	_dwStyle = style;

	SetWindowLongPtr(_hWnd, GWL_EXSTYLE, _dwStyle);
}

int Window::GetSwapChain() const {
	return _iSwapChain;
}

void Window::_UpdateWindowState() {
	if (!_hWnd) return;

	RECT ClientRect;
	ClientRect.left = 0;
	ClientRect.top = 0;
	ClientRect.right = _iWidth;
	ClientRect.bottom = _iHeight;

	RECT WindowRect = ClientRect;
	AdjustWindowRect(&WindowRect, _dwStyle, FALSE);

	int deltaX = (WindowRect.right - ClientRect.right) / 2;
	int deltaY = (WindowRect.bottom - ClientRect.bottom) / 2;

	MoveWindow(_hWnd, _iLeft - deltaX, _iTop - deltaY, _iWidth + deltaX * 2, _iHeight + deltaY * 2, true);
}

