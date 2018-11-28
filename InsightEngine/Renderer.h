#pragma once

namespace insight {
	class Renderer {
	public:
		Renderer();
		~Renderer();

		static Renderer* Get();

		bool Initialize(D3D_DRIVER_TYPE driverType, D3D_FEATURE_LEVEL featureLevel);
		void Shutdown();

		bool CreateSwapChain(const HWND& hwnd);

		bool CreateTexture2D();

		bool CreateRenderTargetView();
		bool CreateDepthStencilView();

		void Present();
		bool Extra();
	protected:
		static Renderer* spRenderer;

		ID3D11Device* _pDevice = nullptr;
		ID3D11DeviceContext* _pDeviceContext = nullptr;
		IDXGISwapChain* _pSwapChain = nullptr;
		ID3D11Texture2D* _pBackBuffer = nullptr;
		D3D11_TEXTURE2D_DESC _BackBufferDesc;
		ID3D11RenderTargetView* _pRenderTargetView = nullptr;
		ID3D11DepthStencilView* _pDepthStencilView = nullptr;
	};
}