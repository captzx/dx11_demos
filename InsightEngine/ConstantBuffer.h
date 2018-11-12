#pragma once
#include "Buffer.h"

namespace insight{
	class ConstantBuffer : public Buffer {
	public:
		ConstantBuffer();
		virtual ~ConstantBuffer();


	public:
		ResourceType GetType();
	};
}