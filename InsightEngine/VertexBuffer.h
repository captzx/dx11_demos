#pragma once
#include "Buffer.h"

namespace insight {
	class VertexBuffer :public Buffer {
	public:
		VertexBuffer(std::shared_ptr<ID3D11Buffer> pBuffer);
		virtual ~VertexBuffer();

		void SetVertexSize(int size);
		void SetVertexCount(int count);

	public:
		ResourceType	GetType();

	protected:
		int _size;
		int _count;
	};
}