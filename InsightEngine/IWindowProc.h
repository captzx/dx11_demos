#pragma once

namespace insight{
	class IWindowProc{
	public:
		virtual LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) = 0;
	};
};
	
