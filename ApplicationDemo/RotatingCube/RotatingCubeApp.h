#pragma once
#include "Application.h"

namespace insight {
	class RenderEffect;
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
		ID3D11RenderTargetView* pRenderTargetView;
		ID3D11DepthStencilView* pDepthStencilView;

		RenderEffect*		_pEffect;

		int _iVertexLayout;
		ID3D11Buffer* _pVertexBuffer;
		ID3D11Buffer* _pIndexBuffer;

		XMFLOAT4X4 _worldMatrix;
		XMFLOAT4X4 _viewMatrix;
		XMFLOAT4X4 _projMatrix;
	};
}
