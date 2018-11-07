#pragma once
#include "IMsgProc.h"

namespace insight {
	class Window{
	public:
		Window();
		virtual ~Window();
	public:
		virtual void Initialize(IMsgProc* WindowProcObj) = 0;
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
		void SetCaption(std::wstring& caption);

		void SetSize(int width, int height);
		void SetPosition(int left, int top);

		int GetSwapChain();
		void SetSwapChain(int swapchain);

		void ResizeWindow(int width, int height);
	protected:
		void UpdateWindowState();

		HWND			hwnd;
		std::wstring	caption;
		int				width;
		int				height;
		int				left;
		int				top;

		int				swapChain;

		DWORD			style;
	};
}