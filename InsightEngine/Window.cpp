#include "pch.h"
#include "Window.h"

using namespace insight;

Window::Window(){
	_hWnd = 0;
	_style = (WS_OVERLAPPEDWINDOW | WS_VISIBLE);
	_caption = L"App";
	_width = 1600;
	_height = 900;
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	_left = (screenWidth - _width) / 2;
	_top = (screenHeight - _height) / 2;

	_swapChain = -1;
}

Window::~Window(){

}

HWND Window::GetHandle(){
	return(_hWnd);
}

void Window::SetWidth(int width){
	_width = width;
	_UpdateWindowState();
}
void Window::SetHeight(int height){
	_height = height;
	_UpdateWindowState();
}

int Window::GetWidth(){
	RECT rect;
	GetClientRect(_hWnd, &rect);
	return(rect.right - rect.left);
}

int Window::GetHeight(){
	RECT rect;
	GetClientRect(_hWnd, &rect);

	return(rect.bottom - rect.top);
}

int Window::GetLeft(){
	POINT point;
	point.x = 0;
	point.y = 0;

	ClientToScreen(_hWnd, &point);

	return(point.x);
}

int Window::GetTop(){
	POINT point;
	point.x = 0;
	point.y = 0;

	ClientToScreen(_hWnd, &point);

	return(point.y);
}

void Window::SetSize(int width, int height){
	_width = width;
	_height = height;

	_UpdateWindowState();
}

void Window::SetPosition(int left, int top){
	_left = left;
	_top = top;

	_UpdateWindowState();
}

void Window::SetCaption(const std::wstring& caption){
	_caption = caption;

	if (_hWnd != 0)
		SetWindowText(_hWnd, caption.c_str());
}

void Window::ResizeWindow(int width, int height){
	_width = width;
	_height = height;
}

std::wstring Window::GetCaption(){
	return(_caption);
}

int Window::GetSwapChain(){
	return(_swapChain);
}

void Window::SetSwapChain(int swapchain){
	_swapChain = swapchain;
}

void Window::_UpdateWindowState(){
	if (_hWnd != 0){
		RECT ClientRect;
		ClientRect.left = 0;
		ClientRect.top = 0;
		ClientRect.right = _width;
		ClientRect.bottom = _height;

		RECT WindowRect = ClientRect;
		AdjustWindowRect(&WindowRect, _style, FALSE);

		int deltaX = (WindowRect.right - ClientRect.right) / 2;
		int deltaY = (WindowRect.bottom - ClientRect.bottom) / 2;

		MoveWindow(_hWnd, _left - deltaX, _top - deltaY,
			_width + deltaX * 2, _height + deltaY * 2, true);
	}
}

void Window::SetStyle(DWORD style){
	_style = style;

	SetWindowLongPtr(_hWnd, GWL_EXSTYLE, _style);
}

DWORD Window::GetStyle(){
	return(_style);
}

