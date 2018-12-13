#pragma once
namespace insight {
	class SwapChainDesc {
	public:
		SwapChainDesc();
		~SwapChainDesc();

		DXGI_SWAP_CHAIN_DESC Get() const;

		void SetDefault();

		void SetWidth(int width);
		void SetHeight(int height);
		void SetOutputWindow(const HWND& hwnd);
	private:
		DXGI_SWAP_CHAIN_DESC _scDesc;
	};

	class SwapChain {
	public:
		SwapChain();

		IDXGISwapChain* &Get();
	protected:
		IDXGISwapChain* _pSwapChain;
	};
}