#pragma once
#include "IWindowProc.h"

namespace insight {
	class Window;
	class Renderer;
	class Application: public IWindowProc {
	public:
		Application();
		virtual ~Application();

		static Application* Get();

		virtual bool ConfigureEngineComponent() = 0;
		virtual void ShutdownEngineComponent() = 0;
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;

		virtual std::wstring GetName() = 0;

		virtual void MessageLoop();
		void RequestTermination();

		LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) override;

	protected:
		static Application* spApplication;

		Renderer* _pRenderer;
		Window* _pWindow;
	};
}