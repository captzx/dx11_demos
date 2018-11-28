#pragma once
namespace insight {
	class SwapChain {
	public:
		SwapChain();

		DXGI_SWAP_CHAIN_DESC GetDesc() const;
		IDXGISwapChain* &Get();
	protected:
		DXGI_SWAP_CHAIN_DESC _desc;
		IDXGISwapChain* _pSwapChain;
	};
}