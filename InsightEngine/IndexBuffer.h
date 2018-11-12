#pragma once
#include "Buffer.h"

namespace insight {
	class IndexBuffer :public Buffer {
	public:
		IndexBuffer(std::shared_ptr<ID3D11Buffer> pBuffer);
		~IndexBuffer();

		void SetIndexSize(int size);
		void SetIndexCount(int count);

	public:
		ResourceType GetType();
	
	protected:
		int _size;
		int _count;
	};
}