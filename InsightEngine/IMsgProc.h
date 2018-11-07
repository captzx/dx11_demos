#pragma once

namespace insight
{
	// This class is the interface for window's message handling
	class IMsgProc
	{
	public:
		virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) = 0;
		virtual void BeforeRegisterWindowClass(WNDCLASSEX &wc) = 0;
	};
};