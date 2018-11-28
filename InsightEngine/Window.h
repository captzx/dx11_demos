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

		HWND& GetHandle();

		int GetLeft() const;
		int GetTop() const;

		DWORD GetStyle() const;
		void SetStyle(DWORD dStyle);

		int GetWidth() const;
		void SetWidth(int width);

		int GetHeight() const;
		void SetHeight(int height);

		std::wstring GetCaption() const;
		void SetCaption(const std::wstring& caption);

		void SetSize(int width, int height);
		void SetPosition(int left, int top);

		int GetSwapChain() const;
		void SetSwapChain(int swapchain);

		POINT GetCursorPosition() const;
		void ResizeWindow(int width, int height);

	protected:
		HWND _hwnd = NULL;
		DWORD _dwStyle = (WS_OVERLAPPEDWINDOW | WS_VISIBLE);
		std::wstring _wsCaption = L"App";
		int	_iWidth = 800;
		int	_iHeight = 600;
		int	_iLeft;
		int	_iTop;

		int	_iSwapChain = -1;

		void _UpdateWindowState();
	};
}