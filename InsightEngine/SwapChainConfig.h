#pragma once

namespace insight {
	class SwapChainConfig{
	public:
		SwapChainConfig();
		virtual ~SwapChainConfig();
		
		void SetDefaults();

		void SetWidth(UINT width);
		void SetHeight(UINT height);
		void SetRefreshRateNumerator(UINT numerator);
		void SetRefreshRateDenominator(UINT denominator);
		void SetFormat(DXGI_FORMAT Format);
		void SetScanlineOrder(DXGI_MODE_SCANLINE_ORDER ScanlineOrdering);
		void SetScaling(DXGI_MODE_SCALING Scaling);


		void SetBufferDesc(DXGI_MODE_DESC BufferDesc);
		void SetSampleDesc(DXGI_SAMPLE_DESC SampleDesc);
		void SetBufferUsage(DXGI_USAGE BufferUsage);
		void SetBufferCount(UINT BufferCount);
		void SetOutputWindow(HWND OutputWindow);
		void SetWindowed(bool Windowed);
		void SetSwapEffect(DXGI_SWAP_EFFECT SwapEffect);
		void SetFlags(UINT Flags);

		DXGI_SWAP_CHAIN_DESC GetDesc();

	protected:
		DXGI_SWAP_CHAIN_DESC _state;
	};
}