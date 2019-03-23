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

	public:
		HWND GetHandle() const;
		int GetSwapChain() const;

		int GetLeft() const;
		int GetTop() const;
		int GetWidth() const;
		int GetHeight() const;
		DWORD GetStyle() const;
		std::wstring GetCaption() const;
		POINT GetCursorPosition() const;

		void SetStyle(DWORD dStyle);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetCaption(const std::wstring& caption);
		void SetSize(int width, int height);
		void SetPosition(int left, int top);
		void SetSwapChain(int swapchain);

		void ResizeWindow(int width, int height);

	protected:
		void _UpdateWindowState();

	protected:
		HWND _hWnd = NULL;

		DWORD _dwStyle = (WS_OVERLAPPEDWINDOW | WS_VISIBLE);
		std::wstring _wsCaption = L"App";
		int	_iWidth = 800;
		int	_iHeight = 600;
		int	_iLeft;
		int	_iTop;

		int	_iSwapChain = -1;
	};
}