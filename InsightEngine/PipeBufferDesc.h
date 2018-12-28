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

		void SetByteWidth(UINT ByteWidth) { _bd.ByteWidth = ByteWidth; }
		void SetUsage(D3D11_USAGE Usage) { _bd.Usage = Usage; }
		void SetBindFlags(UINT BindFlags) { _bd.BindFlags = BindFlags; }
		void SetCPUAccessFlags(UINT CPUAccessFlags) { _bd.CPUAccessFlags = CPUAccessFlags; }
		void SetMiscFlags(UINT MiscFlags) { _bd.MiscFlags = MiscFlags; }
		void SetStrucetureByteStride(UINT StructureByteStride) { _bd.StructureByteStride = StructureByteStride; }

		D3D11_BUFFER_DESC Get() { return _bd; }
	private:
		D3D11_BUFFER_DESC _bd;
	};

}