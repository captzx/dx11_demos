#pragma once
#include "IWindowProc.h"

namespace insight {
	class Scene;
	class Timer;
	class Application:public IWindowProc {
	public:
		Application();
		virtual ~Application();

		static Application* GetApplication();

		virtual bool ConfigureEngineComponent() = 0;
		virtual void ShutdownEngineComponent() = 0;
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;

		virtual std::wstring GetName() = 0;

		virtual void MessageLoop();
		void RequestTerimation();

		virtual LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		virtual void BeforeRegisterWindowClass(WNDCLASSEX &wc);

	protected:
		static Application* _spApplication;

		Scene* _pScene;
		Timer* _pTimer;
	};
}