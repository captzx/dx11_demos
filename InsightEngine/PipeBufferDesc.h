#pragma once

namespace insight {
	class PipeBufferDesc {
	public:
		PipeBufferDesc() { SetDefault(); }
		~PipeBufferDesc() {}
	public:
		void SetDefault();
		void SetAsVertexBuffer(UINT size, bool isDynamic = false);
		void SetAsIndexBuffer(UINT size, bool isDynamic = false);
		void SetAsConstantBuffer(UINT size, bool isDynamic = false);

		void SetByteWidth(UINT ByteWidth) { _bufferDesc.ByteWidth = ByteWidth; }
		void SetUsage(D3D11_USAGE Usage) { _bufferDesc.Usage = Usage; }
		void SetBindFlags(UINT BindFlags) { _bufferDesc.BindFlags = BindFlags; }
		void SetCPUAccessFlags(UINT CPUAccessFlags) { _bufferDesc.CPUAccessFlags = CPUAccessFlags; }
		void SetMiscFlags(UINT MiscFlags) { _bufferDesc.MiscFlags = MiscFlags; }
		void SetStrucetureByteStride(UINT StructureByteStride) { _bufferDesc.StructureByteStride = StructureByteStride; }

		D3D11_BUFFER_DESC Get() { return _bufferDesc; }
	private:
		D3D11_BUFFER_DESC _bufferDesc;
	};

}