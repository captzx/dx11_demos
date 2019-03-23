#include "pch.h"
#include "SwapChain.h"

using namespace insight;

SwapChainDesc::SwapChainDesc() {
	SetDefault();
}
SwapChainDesc::~SwapChainDesc() {

}
DXGI_SWAP_CHAIN_DESC SwapChainDesc::Get() const {
	return _swapChainDesc;
}

void SwapChainDesc::SetDefault() {
	_swapChainDesc.BufferDesc.Width = 1;
	_swapChainDesc.BufferDesc.Height = 1;
	_swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	_swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	_swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	_swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	
	_swapChainDesc.SampleDesc.Count = 1;
	_swapChainDesc.SampleDesc.Quality = 0;
	
	_swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	_swapChainDesc.BufferCount = 1;
	_swapChainDesc.OutputWindow = NULL;
	_swapChainDesc.Windowed = true;
	_swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	_swapChainDesc.Flags = 0;
}

void SwapChainDesc::SetWidth(int width) {
	_swapChainDesc.BufferDesc.Width = width;
}
void SwapChainDesc::SetHeight(int height) {
	_swapChainDesc.BufferDesc.Height = height;
}
void SwapChainDesc::SetOutputWindow(const HWND& hwnd) {
	_swapChainDesc.OutputWindow = hwnd;
}
