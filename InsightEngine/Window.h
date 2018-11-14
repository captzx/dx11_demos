#pragma once
#include "IWindowProc.h"

namespace insight {
	class Window{
	public:
		Window();
		virtual ~Window();
	public:
		virtual void Initialize(IWindowProc* windowProc) = 0;
		virtual void Shutdown() = 0;
		virtual void Paint() = 0;
	public:
		HWND GetHandle();

		int GetLeft();
		int GetTop();

		DWORD GetStyle();
		void SetStyle(DWORD dStyle);

		int GetWidth();
		void SetWidth(int width);

		int GetHeight();
		void SetHeight(int height);

		std::wstring GetCaption();
		void SetCaption(const std::wstring& caption);

		void SetSize(int width, int height);
		void SetPosition(int left, int top);

		int GetSwapChain();
		void SetSwapChain(int swapchain);

		void ResizeWindow(int width, int height);

	protected:
		HWND			_hWnd;
		std::wstring	_caption;
		int				_width;
		int				_height;
		int				_left;
		int				_top;

		int				_swapChain;

		DWORD			_style;


		void _UpdateWindowState();
	};
}