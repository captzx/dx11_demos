#include "pch.h"
#include "DepthStencilViewConfig.h"

using namespace insight;

DepthStencilViewConfig::DepthStencilViewConfig() {
	SetDefaults();
}

DepthStencilViewConfig::~DepthStencilViewConfig() {

}

void DepthStencilViewConfig::SetDefaults() {
	_state.Flags = 0;
	_state.Format = DXGI_FORMAT_UNKNOWN;
	_state.ViewDimension = D3D11_DSV_DIMENSION_UNKNOWN;
}

void DepthStencilViewConfig::SetFormat(DXGI_FORMAT format) {
	_state.Format = format;
}

void DepthStencilViewConfig::SetViewDimension(D3D11_DSV_DIMENSION viewDimension) {
	_state.ViewDimension = viewDimension;
}

void DepthStencilViewConfig::SetFlags(UINT flags) {
	_state.Flags = flags;
}

void DepthStencilViewConfig::SetTexture1D(D3D11_TEX1D_DSV texture1D) {
	_state.Texture1D = texture1D;
}

void DepthStencilViewConfig::SetTexture1DArray(D3D11_TEX1D_ARRAY_DSV texture1DArray) {
	_state.Texture1DArray = texture1DArray;
}

void DepthStencilViewConfig::SetTexture2D(D3D11_TEX2D_DSV texture2D) {
	_state.Texture2D = texture2D;
}

void DepthStencilViewConfig::SetTexture2DArray(D3D11_TEX2D_ARRAY_DSV texture2DArray) {
	_state.Texture2DArray = texture2DArray;
}

void DepthStencilViewConfig::SetTexture2DMS(D3D11_TEX2DMS_DSV texture2DMS) {
	_state.Texture2DMS = texture2DMS;
}

void DepthStencilViewConfig::SetTexture2DMSArray(D3D11_TEX2DMS_ARRAY_DSV texture2DMSArray) {
	_state.Texture2DMSArray = texture2DMSArray;
}

D3D11_DEPTH_STENCIL_VIEW_DESC& DepthStencilViewConfig::GetDesc() {
	return _state;
}

