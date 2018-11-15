#pragma once
#include "Resource.h"

namespace insight {
	class Texture2D: public Resource {
	public:
		explicit Texture2D(ID3D11Texture2D* pTex);
		virtual ~Texture2D();

		void CreateTexture(void* pData);

		D3D11_TEXTURE2D_DESC GetActualDescription();
		D3D11_TEXTURE2D_DESC GetDesiredDescription();

		void SetDesiredDescription(D3D11_TEXTURE2D_DESC description);

		//virtual UINT GetEvictionPriority();
		//virtual void SetEvictionPriority(UINT EvictionPriority);

		virtual ID3D11Resource*	GetResource();
		virtual ResourceType GetType();

	protected:
		ID3D11Texture2D* _pTexture;
		D3D11_TEXTURE2D_DESC _desiredDesc;
		D3D11_TEXTURE2D_DESC _actualDesc;
	};
}