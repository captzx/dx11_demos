#include "pch.h"
#include "SwapChain.h"
#include "ResourceProxy.h"

using namespace insight;

SwapChain::SwapChain(IDXGISwapChain* pSwapChain, std::shared_ptr<ResourceProxy> pResource) {
	_pSwapChain = pSwapChain;
	_pResource = pResource;
}

SwapChain::~SwapChain() {

}

std::shared_ptr<ResourceProxy> SwapChain::GetResource() {
	return _pResource;
}

IDXGISwapChain* SwapChain::Get() {
	return _pSwapChain;
}