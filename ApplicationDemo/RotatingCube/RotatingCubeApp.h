#pragma once
#include "Application.h"

namespace insight {
	class RotatingCubeApp : public Application {
	public:
	public:
		virtual bool ConfigureEngineComponent() override;
		virtual void ShutdownEngineComponent() override;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Shutdown() override;

		virtual std::wstring GetName() override;
	};
}
