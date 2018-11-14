#include "pch.h"
#include "SwapChainConfig.h"

using namespace insight;

SwapChainConfig::SwapChainConfig() {
	SetDefaults();
}
SwapChainConfig::~SwapChainConfig() {

}

void SwapChainConfig::SetDefaults() {
	_state.BufferDesc.Width = 1;
	_state.BufferDesc.Height = 1;
	_state.BufferDesc.RefreshRate.Numerator = 60;
	_state.BufferDesc.RefreshRate.Denominator = 1;
	_state.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	_state.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	_state.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	_state.SampleDesc.Count = 1;
	_state.SampleDesc.Quality = 0;
	
	_state.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	_state.BufferCount = 2;
	_state.OutputWindow = 0;
	_state.Windowed = true;
	_state.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	_state.Flags = 0;
}

void SwapChainConfig::SetWidth(UINT width) {
	_state.BufferDesc.Width = width;
}

void SwapChainConfig::SetHeight(UINT height) {
	_state.BufferDesc.Height = height;
}

void SwapChainConfig::SetRefreshRateNumerator(UINT numerator) {
	_state.BufferDesc.RefreshRate.Numerator = numerator;
}

void SwapChainConfig::SetRefreshRateDenominator(UINT denominator) {
	_state.BufferDesc.RefreshRate.Denominator = 1;
}

void SwapChainConfig::SetFormat(DXGI_FORMAT Format) {
	_state.BufferDesc.Format = Format;
}

void SwapChainConfig::SetScanlineOrder(DXGI_MODE_SCANLINE_ORDER ScanlineOrdering) {
	_state.BufferDesc.ScanlineOrdering = ScanlineOrdering;
}

void SwapChainConfig::SetScaling(DXGI_MODE_SCALING Scaling) {
	_state.BufferDesc.Scaling = Scaling;
}

void SwapChainConfig::SetBufferDesc(DXGI_MODE_DESC BufferDesc) {
	_state.BufferDesc = BufferDesc;
}

void SwapChainConfig::SetSampleDesc(DXGI_SAMPLE_DESC SampleDesc) {
	_state.SampleDesc = SampleDesc;
}

void SwapChainConfig::SetBufferUsage(DXGI_USAGE BufferUsage) {
	_state.BufferUsage = BufferUsage;
}

void SwapChainConfig::SetBufferCount(UINT BufferCount) {
	_state.BufferCount = BufferCount;
}

void SwapChainConfig::SetOutputWindow(HWND OutputWindow) {
	_state.OutputWindow = OutputWindow;
}

void SwapChainConfig::SetWindowed(bool Windowed) {
	_state.Windowed = Windowed;
}

void SwapChainConfig::SetSwapEffect(DXGI_SWAP_EFFECT SwapEffect) {
	_state.SwapEffect = SwapEffect;
}

void SwapChainConfig::SetFlags(UINT Flags) {
	_state.Flags = Flags;
}
