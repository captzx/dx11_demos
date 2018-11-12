#pragma once
#include "Resource.h"

namespace insight {
	class Buffer: public Resource {
	public:
		Buffer();
		virtual ~Buffer();

		D3D11_BUFFER_DESC GetActualDescription();

		D3D11_BUFFER_DESC GetDesiredDescription();
		void SetDesiredDescription(D3D11_BUFFER_DESC desc);

		UINT GetByteWidth();
		void SetByteWidht(UINT byteWidth);

		D3D11_USAGE GetUsage();
		void SetUsage(D3D11_USAGE usage);

		UINT GetBindFlags();
		void SetBindFlags(UINT bindFlags);

		UINT GetCPUAccessFlags();
		void SetCPUAccessFlags(UINT cpuAccessFlags);

		UINT GetMiscFlags();
		void SetMiscFlags(UINT miscFlags);

		UINT GetStructureByteStride();
		void SetStructrueByteStride(UINT structureByteStride);

		void* Map();
		void UnMap();

	public:
		ID3D11Buffer* GetResource();

	protected:
		std::shared_ptr<ID3D11Buffer> _pBuffer;

		D3D11_BUFFER_DESC _desiredDesc;
		D3D11_BUFFER_DESC _actualDesc;
	};
}