#pragma once
#include "Resource.h"

namespace insight {
	class Buffer: public Resource {
	public:
		Buffer();
		virtual ~Buffer();


	public:
		ID3D11Resource* GetResource();
		ResourceType GetType();
	protected:
		std::shared_ptr<ID3D11Buffer> pBuffer;
		D3D11_BUFFER_DESC desc;

	};
}