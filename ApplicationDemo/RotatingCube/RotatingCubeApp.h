#pragma once
#include "Application.h"

namespace insight {
	class Renderer;
	class Window;
	class RenderEffect;
	class PipeResourceProxy;
	typedef std::shared_ptr<PipeResourceProxy> ResourcePtr;
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
		ResourcePtr _pRenderTargetView;
		ResourcePtr _pDepthStencilView;
		RenderEffect* _pEffect;
		int _iVertexLayout;
		ResourcePtr _pVertexBuffer;
		ResourcePtr _pIndexBuffer;
	};
}
