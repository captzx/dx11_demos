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

		virtual bool ConfigureEngineComponent();
		virtual void ShutdownEngineComponent();
		virtual void Initialize();
		virtual void Update();
		virtual void Shutdown();

		virtual std::wstring GetName() = 0;

		virtual void MessageLoop();
		void RequestTermination();
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) override;
	protected:
		static Application* spApplication;

		Renderer* _pRenderer = nullptr;
		Window* _pWindow = nullptr;
	};
}