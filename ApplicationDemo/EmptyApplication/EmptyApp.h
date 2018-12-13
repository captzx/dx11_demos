#pragma once
#include "Application.h"
#include <string>

namespace insight {
	class EmptyApp: public Application {
	public:
		virtual bool ConfigureEngineComponent() override;
		virtual void ShutdownEngineComponent() override;
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Shutdown()override;

		std::wstring GetName() override;
	private:
		Renderer* _pRenderer = nullptr;
		Window* _pWindow = nullptr;
	};
}