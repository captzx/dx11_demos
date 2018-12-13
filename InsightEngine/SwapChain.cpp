#include "pch.h"
#include "SwapChain.h"

using namespace insight;

SwapChainDesc::SwapChainDesc() {
	SetDefault();
}
SwapChainDesc::~SwapChainDesc() {

}
DXGI_SWAP_CHAIN_DESC SwapChainDesc::Get() const {
	return _scDesc;
}

void SwapChainDesc::SetDefault() {
	_scDesc.BufferDesc.Width = 1;
	_scDesc.BufferDesc.Height = 1;
	_scDesc.BufferDesc.RefreshRate.Denominator = 1;
	_scDesc.BufferDesc.RefreshRate.Numerator = 60;
	_scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	_scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	_scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	
	_scDesc.SampleDesc.Count = 1;
	_scDesc.SampleDesc.Quality = 0;
	
	_scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	_scDesc.BufferCount = 1;
	_scDesc.OutputWindow = NULL;
	_scDesc.Windowed = true;
	_scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	_scDesc.Flags = 0;
}

void SwapChainDesc::SetWidth(int width) {
	_scDesc.BufferDesc.Width = width;
}
void SwapChainDesc::SetHeight(int height) {
	_scDesc.BufferDesc.Height = height;
}
void SwapChainDesc::SetOutputWindow(const HWND& hwnd) {
	_scDesc.OutputWindow = hwnd;
}


SwapChain::SwapChain() {

}

IDXGISwapChain* &SwapChain::Get() {
	return _pSwapChain;
}