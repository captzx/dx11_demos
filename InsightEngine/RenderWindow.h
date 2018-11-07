#pragma once
#include "IMsgProc.h"
#include "Window.h"

namespace insight {
	class RenderWindow : public Window{
	public:
		RenderWindow();
		virtual ~RenderWindow();
	public:
		virtual void Initialize(IMsgProc* WindowProcObj);
		virtual void Shutdown();
		virtual void Paint();

		POINT GetCursorPosition();
	};
}
