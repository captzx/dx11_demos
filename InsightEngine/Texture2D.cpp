#include "pch.h"
#include "Texture2D.h"

using namespace insight;

Texture2D::Texture2D(ID3D11Texture2D* pTexture) {
	_pTexture = pTexture;

	ZeroMemory(&_desiredDesc, sizeof(D3D11_TEXTURE2D_DESC));
	ZeroMemory(&_actualDesc, sizeof(D3D11_TEXTURE2D_DESC));
}

Texture2D::~Texture2D() {

}

void Texture2D::CreateTexture(void* pData) {

}

D3D11_TEXTURE2D_DESC Texture2D::GetActualDescription() {
	ZeroMemory(&_actualDesc, sizeof(D3D11_TEXTURE2D_DESC));

	if (_pTexture)
		_pTexture->GetDesc(&_actualDesc);

	return(_actualDesc);
}

D3D11_TEXTURE2D_DESC Texture2D::GetDesiredDescription() {
	return _desiredDesc;
}

void Texture2D::SetDesiredDescription(D3D11_TEXTURE2D_DESC desc) {
	_desiredDesc = desc;
}

ID3D11Resource*	Texture2D::GetResource() {
	_pTexture;
}

ResourceType Texture2D::GetType() {
	return RT_TEXTURE2D;
}