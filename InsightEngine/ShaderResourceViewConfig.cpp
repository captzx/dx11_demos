#include "pch.h"
#include "ShaderResourceViewConfig.h"

using namespace insight;

ShaderResourceViewConfig::ShaderResourceViewConfig() {
	SetDefaults();
}

ShaderResourceViewConfig::~ShaderResourceViewConfig() {

}

void ShaderResourceViewConfig::SetDefaults() {
	_state.Format = DXGI_FORMAT_UNKNOWN;
	_state.ViewDimension = D3D11_SRV_DIMENSION_UNKNOWN;
}

void ShaderResourceViewConfig::SetFormat(DXGI_FORMAT format) {
	_state.Format = format;
}

void ShaderResourceViewConfig::SetViewDimension(D3D11_SRV_DIMENSION viewDimension) {
	_state.ViewDimension = viewDimension;
}

void ShaderResourceViewConfig::SetBuffer(D3D11_BUFFER_SRV buffer) {
	_state.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	_state.Buffer = buffer;
}

void ShaderResourceViewConfig::SetTexture1D(D3D11_TEX1D_SRV texture1D) {
	_state.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
	_state.Texture1D = texture1D;
}

void ShaderResourceViewConfig::SetTexture1DArray(D3D11_TEX1D_ARRAY_SRV texture1DArray) {
	_state.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1DARRAY;
	_state.Texture1DArray = texture1DArray;
}

void ShaderResourceViewConfig::SetTexture2D(D3D11_TEX2D_SRV texture2D) {
	_state.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	_state.Texture2D = texture2D;
}

void ShaderResourceViewConfig::SetTexture2DArray(D3D11_TEX2D_ARRAY_SRV texture2DArray) {
	_state.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	_state.Texture2DArray = texture2DArray;
}

void ShaderResourceViewConfig::SetTexture2DMS(D3D11_TEX2DMS_SRV texture2DMS) {
	_state.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
	_state.Texture2DMS = texture2DMS;
}

void ShaderResourceViewConfig::SetTexture2DMSArray(D3D11_TEX2DMS_ARRAY_SRV texture2DMSArray) {
	_state.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY;
	_state.Texture2DMSArray = texture2DMSArray;
}

void ShaderResourceViewConfig::SetTexture3D(D3D11_TEX3D_SRV texture3D) {
	_state.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
	_state.Texture3D = texture3D;
}

D3D11_SHADER_RESOURCE_VIEW_DESC& ShaderResourceViewConfig::GetSRVDesc() {
	return _state;
}
