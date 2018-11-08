#pragma once
#include "Buffer.h"

namespace insight {
	class VertexBuffer :public Buffer {
	public:
		VertexBuffer(Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer);
		virtual ~VertexBuffer();

	public:
		ResourceType	GetType();

	protected:

	};
}