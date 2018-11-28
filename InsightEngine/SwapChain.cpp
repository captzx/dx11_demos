#include "pch.h"
#include "SwapChain.h"

using namespace insight;

SwapChain::SwapChain() {

}


DXGI_SWAP_CHAIN_DESC SwapChain::GetDesc() const {
	return _desc;
}

IDXGISwapChain* &SwapChain::Get() {
	return _pSwapChain;
}