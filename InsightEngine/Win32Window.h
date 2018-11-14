#pragma once
#include "Window.h"

namespace insight {
	class IWindowProc;
	class Win32Window : public Window{
	public:
		Win32Window();
		virtual ~Win32Window();

	public:
		virtual void Initialize(IWindowProc* windowProc);
		virtual void Shutdown();
		virtual void Paint();

		POINT GetCursorPosition();
	};
}
