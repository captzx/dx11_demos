#include "pch.h"
#include "PipeTextureDesc.h"

using namespace insight;

void Texture1dDesc::SetDefaults() {

}

void Texture2dDesc::SetDefaults() {

}

void Texture2dDesc::SetDepthBuffer(UINT width, UINT height){
	_t2dDesc.Width = width;
	_t2dDesc.Height = height;
	_t2dDesc.MipLevels = 1;
	_t2dDesc.ArraySize = 1;
	_t2dDesc.Format = DXGI_FORMAT_D32_FLOAT;
	_t2dDesc.SampleDesc.Count = 1;
	_t2dDesc.SampleDesc.Quality = 0;
	_t2dDesc.Usage = D3D11_USAGE_DEFAULT;
	_t2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	_t2dDesc.CPUAccessFlags = 0;
	_t2dDesc.MiscFlags = 0;
}

void Texture2dDesc::SetColorBuffer(UINT width, UINT height) {
	_t2dDesc.Width = width;
	_t2dDesc.Height = height;
	_t2dDesc.MipLevels = 1;
	_t2dDesc.ArraySize = 1;
	_t2dDesc.Format = DXGI_FORMAT_D32_FLOAT;
	_t2dDesc.SampleDesc.Count = 1;
	_t2dDesc.SampleDesc.Quality = 0;
	_t2dDesc.Usage = D3D11_USAGE_DEFAULT;
	_t2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	_t2dDesc.CPUAccessFlags = 0;
	_t2dDesc.MiscFlags = 0;
}
void Texture3dDesc::SetDefaults() {

}
