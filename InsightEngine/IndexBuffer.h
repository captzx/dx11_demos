#pragma once
#include "Buffer.h"

namespace insight {
	class IndexBuffer :public Buffer {
	public:
		IndexBuffer(std::shared_ptr<ID3D11Buffer> pBuffer);
		~IndexBuffer();

	protected:

	};
}