#include "pch.h"
#include "Texture2DConfig.h"

using namespace insight;

Texture2DConfig::Texture2DConfig() {
	SetDefaults();
}


Texture2DConfig::~Texture2DConfig() {

}


void Texture2DConfig::SetDefaults() {
	_state.Width = 1;
	_state.Height = 1;
	_state.MipLevels = 1;
	_state.ArraySize = 1;
	_state.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

	_state.SampleDesc.Count = 1;
	_state.SampleDesc.Quality = 0;

	_state.Usage = D3D11_USAGE_DEFAULT;
	_state.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	_state.CPUAccessFlags = 0;
	_state.MiscFlags = 0;
}

void Texture2DConfig::SetDepthBuffer(UINT width, UINT height) {
	_state.Width = width;
	_state.Height = height;
	_state.MipLevels = 1;
	_state.ArraySize = 1;
	_state.Format = DXGI_FORMAT_D32_FLOAT;

	_state.SampleDesc.Count = 1;
	_state.SampleDesc.Quality = 0;

	_state.Usage = D3D11_USAGE_DEFAULT;
	_state.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	_state.CPUAccessFlags = 0;
	_state.MiscFlags = 0;
}

void Texture2DConfig::SetColorBuffer(UINT width, UINT height) {
	_state.Width = width;
	_state.Height = height;
	_state.MipLevels = 1;
	_state.ArraySize = 1;
	_state.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;

	_state.SampleDesc.Count = 1;
	_state.SampleDesc.Quality = 0;

	_state.Usage = D3D11_USAGE_DEFAULT;
	_state.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	_state.CPUAccessFlags = 0;
	_state.MiscFlags = 0;
}

void Texture2DConfig::SetWidth(UINT width) {
	_state.Width = width;
}

void Texture2DConfig::SetHeight(UINT height) {
	_state.Height = height;
}

void Texture2DConfig::SetMipLevels(UINT mipLevels) {
	_state.MipLevels = mipLevels;
}

void Texture2DConfig::SetArraySize(UINT arraySize) {
	_state.ArraySize = arraySize;
}

void Texture2DConfig::SetFormat(DXGI_FORMAT format) {
	_state.Format = format;
}

void Texture2DConfig::SetSampleDesc(DXGI_SAMPLE_DESC desc) {
	_state.SampleDesc = desc;
}

void Texture2DConfig::SetUsage(D3D11_USAGE usage) {
	_state.Usage = usage;
}

void Texture2DConfig::SetBindFlags(UINT bindFlags) {
	_state.BindFlags = bindFlags;
}

void Texture2DConfig::SetCPUAccessFlags(UINT CPUAccessFlags) {
	_state.CPUAccessFlags = CPUAccessFlags;
}

void Texture2DConfig::SetMiscFlags(UINT miscFlags) {
	_state.MiscFlags = miscFlags;
}


D3D11_TEXTURE2D_DESC Texture2DConfig::GetDesc() {
	return _state;
}
