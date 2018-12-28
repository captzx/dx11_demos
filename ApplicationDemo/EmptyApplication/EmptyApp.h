#pragma once
#include "Application.h"
#include <string>
#include "PipeResourceProxy.h"

namespace insight {
	struct Vertex {
		XMFLOAT3 Pos;
		XMFLOAT4 Color;
	};

	class RenderEffect;
	class Renderer;
	class Window;
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

		int	_iSwapChain;
		ResourcePtr _pRenderTargetView;
		ResourcePtr _pDepthStencilView;
		RenderEffect* _pEffect;
		int _iVertexLayout;
		ResourcePtr _pVertexBuffer; 
		ResourcePtr _pIndexBuffer;
	};
}