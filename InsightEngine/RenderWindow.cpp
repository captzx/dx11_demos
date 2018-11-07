#include "PCH.h"
#include "RenderWindow.h"

using namespace insight;

extern LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
RenderWindow::RenderWindow(){
	hwnd = 0;
	style = (WS_OVERLAPPEDWINDOW | WS_VISIBLE);
}

RenderWindow::~RenderWindow(){
	Shutdown();
}

// This free function is used as a hook into the window's messaging system.  When
// the window is initialized, the owner passes a pointer to a IWindowProc 
// implementation.  When Windows sends a message to this window, we call this 
// handler function - which will either call the default processor (when no valid
// pointer is there) or call the IWindowProc method (when a valid one is 
// available).
LRESULT CALLBACK InternalWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
	LONG_PTR ObjPtr = GetWindowLongPtr(hwnd, 0);

	if (ObjPtr == 0) {
		return(DefWindowProc(hwnd, msg, wparam, lparam));
	}
	else {
		return(((IMsgProc*)ObjPtr)->MsgProc(hwnd, msg, wparam, lparam));
	}
}

void RenderWindow::Initialize(IMsgProc* MsgProc){
	WNDCLASSEX wc;

	// Setup the window class
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
	wc.lpszClassName = L"Win32";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (MsgProc != nullptr) {
		MsgProc->BeforeRegisterWindowClass(wc);
	}

	// Register the window class
	RegisterClassEx(&wc);

	// Record the desired device size
	RECT rc;
	rc.top = rc.left = 0;
	rc.right = width;
	rc.bottom = height;

	// Adjust the window size for correct device size
	AdjustWindowRectEx(&rc, style, false, 0);

	long adjust_width = rc.right - rc.left;
	long adjust_height = rc.bottom - rc.top;



	// Create an instance of the window
	hwnd = CreateWindowEx(
		NULL,							// extended style
		wc.lpszClassName, 				// class name
		caption.c_str(),				// instance title
		style,							// window style
		left, top,
		adjust_width, adjust_height,	
		NULL,							// handle to parent 
		NULL,							// handle to menu
		NULL,							// instance of this application
		NULL);							// extra creation parms


	// Update the size of the window according to the client area that was 
	// created.  Due to limitations about the desktop size, this can cause some
	// situations where the created window is smaller than requested.

	RECT rect;
	GetClientRect(hwnd, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;


	if (hwnd) {
		// Set in the "extra" bytes the pointer to the IWindowProc object
		// which handles messages for the window
		SetWindowLongPtr(hwnd, 0, (LONG_PTR)MsgProc);
		// Initially display the window
		ShowWindow(hwnd, SW_SHOWNORMAL);
		UpdateWindow(hwnd);
	}
}

void RenderWindow::Shutdown(){
	if (hwnd)
		DestroyWindow(hwnd);

	hwnd = 0;
}

void RenderWindow::Paint(){

}

POINT RenderWindow::GetCursorPosition(){
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);

	return p;
}
