#pragma once

namespace insight{
	class IWindowProc{
	public:
		virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) = 0;
		virtual void BeforeRegisterWindowClass(WNDCLASSEX &wc) = 0;
	};
};