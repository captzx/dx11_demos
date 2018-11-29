#pragma once

namespace insight {
	class RenderingPipeline;
	class Renderer {
	public:
		Renderer();
		~Renderer();

		bool Initialize(D3D_DRIVER_TYPE driverType, D3D_FEATURE_LEVEL featureLevel);
		void Shutdown();

		bool CreateSwapChain(const HWND& hwnd);

		bool CreateTexture2D();

		bool CreateRenderTargetView();
		bool CreateDepthStencilView();

		void Present();

	public:
		ID3D11RenderTargetView* GetRenderTargetView();
		ID3D11DepthStencilView* GetDepthStencilView();

		RenderingPipeline* GetPipeline()const { return _pImmPipeline; }
	protected:
		ID3D11Device* _pDevice = nullptr;
		RenderingPipeline* _pImmPipeline = nullptr;


		IDXGISwapChain* _pSwapChain = nullptr;
		ID3D11Texture2D* _pBackBuffer = nullptr;
		D3D11_TEXTURE2D_DESC _BackBufferDesc;

		ID3D11RenderTargetView* _pRenderTargetView = nullptr;
		ID3D11DepthStencilView* _pDepthStencilView = nullptr;
	};
}