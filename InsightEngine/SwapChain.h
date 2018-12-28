#pragma once
#include "PipeResourceProxy.h"

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
		explicit SwapChain(ComPtr<IDXGISwapChain> pSwapChain, ResourcePtr resource) {
			_pSwapChain = pSwapChain;
			_Resource = resource;
		}
		virtual ~SwapChain() {

		}

		IDXGISwapChain* Get() {
			return _pSwapChain.Get();
		}
		ResourcePtr GetBuffer() { return _Resource; }

	protected:
		ComPtr<IDXGISwapChain> _pSwapChain;
		ResourcePtr _Resource;
	};
}