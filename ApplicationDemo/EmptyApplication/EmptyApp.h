#pragma once
#include "Application.h"

namespace insight {
	class RenderEffect;
	class Renderer;
	class Window;
	class PipeResourceProxy;
	class EmptyApp: public Application {
	public:
		EmptyApp() {}
		virtual ~EmptyApp() {}
	public:
		virtual bool ConfigureEngineComponent() override;
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Shutdown()override;
		virtual void ShutdownEngineComponent() override;
		virtual std::wstring GetName() override;

	private:
		Window* _pWindow = nullptr;
		Renderer* _pRenderer = nullptr;

		std::shared_ptr<PipeResourceProxy> _pRenderTargetView;
		std::shared_ptr<PipeResourceProxy> _pDepthStencilView;

		int	_iSwapChain;
	};
}