#pragma once
#include "Application.h"

namespace insight {
	class Renderer;
	class Window;
	class RenderEffect;
	class PipeResourceProxy;

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
		RenderEffect* _pEffect = nullptr;

		std::shared_ptr<PipeResourceProxy> _pRenderTargetView;
		std::shared_ptr<PipeResourceProxy> _pDepthStencilView;
		std::shared_ptr<PipeResourceProxy> _pVertexBuffer;
		std::shared_ptr<PipeResourceProxy> _pIndexBuffer;
		std::shared_ptr<PipeResourceProxy> _pConstantBuffer;

		int	_iSwapChain;
		int _iVertexLayout;

		XMFLOAT4X4 _f4x4World;
		XMFLOAT4X4 _f4x4View;
		XMFLOAT4X4 _f4x4Proj;
	};
}
