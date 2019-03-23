#include "pch.h"
#include "PipeTexture.h"

using namespace insight;

Texture2D::Texture2D(ComPtr<ID3D11Texture2D> pTex) {
	_pTexture = pTex;
	ZeroMemory(&_desiredDesc, sizeof(D3D11_TEXTURE2D_DESC));
	ZeroMemory(&_actualDesc, sizeof(D3D11_TEXTURE2D_DESC));
}

D3D11_TEXTURE2D_DESC Texture2D::GetActualDescription() {
	ZeroMemory(&_actualDesc, sizeof(D3D11_TEXTURE2D_DESC));

	if (_pTexture)
		_pTexture->GetDesc(&_actualDesc);

	return(_actualDesc);
}
