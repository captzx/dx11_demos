#pragma once
#include "PipeResource.h"

namespace insight {
	class Texture2D : public PipeResource{
	public:
		explicit Texture2D(ComPtr<ID3D11Texture2D> pTex);
		virtual ~Texture2D() {}

		D3D11_TEXTURE2D_DESC GetActualDescription();
		D3D11_TEXTURE2D_DESC GetDesiredDescription() { return _DesiredDesc; }
		void SetDesiredDescription(D3D11_TEXTURE2D_DESC description) { _DesiredDesc = description; }

		virtual PipeResourceType GetType() override { return PRT_TEXTURE2D; }
		virtual ID3D11Resource*	GetResource() { return _pTexture.Get(); }

	protected:
		ComPtr<ID3D11Texture2D>	_pTexture;
		D3D11_TEXTURE2D_DESC _DesiredDesc;
		D3D11_TEXTURE2D_DESC _ActualDesc;
	};
}