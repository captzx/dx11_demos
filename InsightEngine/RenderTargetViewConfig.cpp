#include "pch.h"
#include "RenderTargetViewConfig.h"

using namespace insight;

RenderTargetViewConfig::RenderTargetViewConfig() {
	SetDefaults();
}

RenderTargetViewConfig::~RenderTargetViewConfig() {

}

void RenderTargetViewConfig::SetDefaults() {
	_state.Format = DXGI_FORMAT_UNKNOWN;
	_state.ViewDimension = D3D11_RTV_DIMENSION_UNKNOWN;
}

void RenderTargetViewConfig::SetFormat(DXGI_FORMAT format) {
	_state.Format = format;
}

void RenderTargetViewConfig::SetViewDimension(D3D11_RTV_DIMENSION viewDimension) {
	_state.ViewDimension = viewDimension;
}

void RenderTargetViewConfig::SetBuffer(D3D11_BUFFER_RTV buffer) {
	_state.ViewDimension = D3D11_RTV_DIMENSION_BUFFER;
	_state.Buffer = buffer;
}

void RenderTargetViewConfig::SetTexture1D(D3D11_TEX1D_RTV texture1D) {
	_state.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1D;
	_state.Texture1D = texture1D;
}

void RenderTargetViewConfig::SetTexture1DArray(D3D11_TEX1D_ARRAY_RTV texture1DArray) {
	_state.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE1DARRAY;
	_state.Texture1DArray = texture1DArray;
}

void RenderTargetViewConfig::SetTexture2D(D3D11_TEX2D_RTV texture2D) {
	_state.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	_state.Texture2D = texture2D;
}

void RenderTargetViewConfig::SetTexture2DArray(D3D11_TEX2D_ARRAY_RTV texture2DArray) {
	_state.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
	_state.Texture2DArray = texture2DArray;
}

void RenderTargetViewConfig::SetTexture2DMS(D3D11_TEX2DMS_RTV texture2DMS) {
	_state.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
	_state.Texture2DMS = texture2DMS;
}

void RenderTargetViewConfig::SetTexture2DMSArray(D3D11_TEX2DMS_ARRAY_RTV texture2DMSArray) {
	_state.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
	_state.Texture2DMSArray = texture2DMSArray;
}

void RenderTargetViewConfig::SetTexture3D(D3D11_TEX3D_RTV texture3D) {
	_state.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE3D;
	_state.Texture3D = texture3D;
}

D3D11_RENDER_TARGET_VIEW_DESC& RenderTargetViewConfig::GetRTVDesc() {
	return _state;
}
