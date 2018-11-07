#include "pch.h"
#include "Window.h"

using namespace insight;

Window::Window(){
	hwnd = 0;
	style = (WS_OVERLAPPEDWINDOW | WS_VISIBLE);
	caption = L"xin-engine";
	width = 1600;
	height = 900;
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	left = (screenWidth - width) / 2;
	top = (screenHeight - height) / 2;

	swapChain = -1;
}

Window::~Window(){

}

HWND Window::GetHandle(){
	return(hwnd);
}

void Window::SetWidth(int width){
	this->width = width;
	UpdateWindowState();
}
void Window::SetHeight(int height){
	this->height = height;
	UpdateWindowState();
}

int Window::GetWidth(){
	RECT rect;
	GetClientRect(hwnd, &rect);
	return(rect.right - rect.left);
}

int Window::GetHeight(){
	RECT rect;
	GetClientRect(hwnd, &rect);

	return(rect.bottom - rect.top);
}

int Window::GetLeft(){
	POINT point;
	point.x = 0;
	point.y = 0;

	ClientToScreen(hwnd, &point);

	return(point.x);
}

int Window::GetTop(){
	POINT point;
	point.x = 0;
	point.y = 0;

	ClientToScreen(hwnd, &point);

	return(point.y);
}

void Window::SetSize(int width, int height){
	this->width = width;
	this->height = height;

	UpdateWindowState();
}

void Window::SetPosition(int left, int top){
	// The position is specified in terms of the client area - so the actual 
	// Win32 function needs to use the modified screen coordinates that will put
	// the window's client area at the desired location.
	this->left = left;
	this->top = top;

	UpdateWindowState();
}

void Window::SetCaption(std::wstring& caption){
	this->caption = caption;

	if (hwnd != 0)
		SetWindowText(hwnd, caption.c_str());
}

void Window::ResizeWindow(int width, int height){
	// This method is called for a WM_SIZE event, so we just update our local
	// state instead of also calling UpdateWindowState().
	this->width = width;
	this->height = height;
}

std::wstring Window::GetCaption(){
	return(caption);
}

int Window::GetSwapChain(){
	return(swapChain);
}

void Window::SetSwapChain(int swapchain){
	this->swapChain = swapchain;
}

void Window::UpdateWindowState(){
	if (hwnd != 0){
		RECT ClientRect;
		ClientRect.left = 0;
		ClientRect.top = 0;
		ClientRect.right = width;
		ClientRect.bottom = height;

		// Adjust the window size for correct device size
		RECT WindowRect = ClientRect;
		AdjustWindowRect(&WindowRect, style, FALSE);

		int deltaX = (WindowRect.right - ClientRect.right) / 2;
		int deltaY = (WindowRect.bottom - ClientRect.bottom) / 2;

		MoveWindow(hwnd, left - deltaX, top - deltaY,
			width + deltaX * 2, height + deltaY * 2, true);
	}
}

void Window::SetStyle(DWORD style){
	this->style = style;

	SetWindowLongPtr(hwnd, GWL_EXSTYLE, this->style);
}

DWORD Window::GetStyle(){
	return(style);
}

