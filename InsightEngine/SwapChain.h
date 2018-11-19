#pragma once

namespace insight {
	class ResourceProxy;
	class SwapChain {
	public:
		explicit SwapChain(IDXGISwapChain* pSwapChain, std::shared_ptr<ResourceProxy> pResource);
		virtual ~SwapChain();

		std::shared_ptr<ResourceProxy> GetResource();

		IDXGISwapChain* Get();

	protected:
		IDXGISwapChain*	_pSwapChain;
		std::shared_ptr<ResourceProxy>	_pResource;
	};
}