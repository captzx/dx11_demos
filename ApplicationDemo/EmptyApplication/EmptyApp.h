#pragma once
#include "Application.h"
#include "PipeResourceProxy.h"

namespace insight {
	class RenderEffect;
	class Renderer;
	class Window;

	struct VSConstBuffer;
	class EmptyApp: public Application {
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

		int	_iSwapChain;
		std::shared_ptr<PipeResourceProxy> _pRenderTargetView;
		std::shared_ptr<PipeResourceProxy> _pDepthStencilView;
		RenderEffect* _pEffect;
		int _iVertexLayout;
		std::shared_ptr<PipeResourceProxy> _pVertexBuffer;
		std::shared_ptr<PipeResourceProxy> _pIndexBuffer;
		std::shared_ptr<PipeResourceProxy> _pConstantBuffer;

		VSConstBuffer* _pVSConstBuffer;
	};
}