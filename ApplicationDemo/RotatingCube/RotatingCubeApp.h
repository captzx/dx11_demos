#pragma once
#include "Application.h"

namespace insight {
	struct CB {
		XMMATRIX w;
		XMMATRIX v;
		XMMATRIX p;
	};

	class Renderer;
	class Window;
	class RenderEffect;
	class PipeResourceProxy;
	typedef std::shared_ptr<PipeResourceProxy> std::shared_ptr<PipeResourceProxy>;
	class RotatingCubeApp : public Application {
	public:
		virtual bool ConfigureEngineComponent() override;
		virtual void ShutdownEngineComponent() override;
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Shutdown()override;

		virtual std::wstring GetName() override;

	private:
		Renderer* _pRenderer = nullptr;
		Window* _pWindow = nullptr;

		int	_iSwapChain;
		std::shared_ptr<PipeResourceProxy> _pRenderTargetView;
		std::shared_ptr<PipeResourceProxy> _pDepthStencilView;
		RenderEffect* _pEffect;
		int _iVertexLayout;
		std::shared_ptr<PipeResourceProxy> _pVertexBuffer;
		std::shared_ptr<PipeResourceProxy> _pIndexBuffer;
		std::shared_ptr<PipeResourceProxy> _pConstantBuffer;

		CB cb;
	};
}
