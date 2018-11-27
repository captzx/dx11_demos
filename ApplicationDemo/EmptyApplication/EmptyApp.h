#pragma once
#include "Application.h"
#include <string>

namespace insight {
	class EmptyApp: public Application {
	public:
		EmptyApp();
		~EmptyApp();

		bool ConfigureEngineComponent() override;
		void ShutdownEngineComponent() override;
		void Initialize() override;
		void Update() override;
		void Shutdown() override;

		std::wstring GetName() override;
	};
}