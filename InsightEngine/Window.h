#pragma once

namespace insight {
	class IWindowProc;
	class Window{
	public:
		Window();
		virtual ~Window();
	public:
		virtual void Initialize(IWindowProc* windowProc);
		virtual void Shutdown();

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
		void SetCaption(std::wstring caption);

		void SetSize(int width, int height);
		void SetPosition(int left, int top);

		int GetSwapChain();
		void SetSwapChain(int swapchain);

		POINT GetCursorPosition();
		void ResizeWindow(int width, int height);

	protected:
		HWND _hwnd;
		DWORD _dwStyle;
		std::wstring _wsCaption;
		int	_iWidth;
		int	_iHeight;
		int	_iLeft;
		int	_iTop;

		int	_iSwapChain;

		void _UpdateWindowState();
	};
}