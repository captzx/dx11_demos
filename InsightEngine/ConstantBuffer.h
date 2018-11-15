#pragma once
#include "Buffer.h"

namespace insight{
	class ConstantBuffer : public Buffer {
	public:
		ConstantBuffer(ID3D11Buffer* pBuffer);
		virtual ~ConstantBuffer();

		void						SetAutoUpdate(bool enable);
		bool						GetAutoUpdate();
	public:
		ResourceType GetType();
	};
}