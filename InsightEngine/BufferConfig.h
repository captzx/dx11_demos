#pragma once

namespace insight {
	class BufferConfig {
	public:
		BufferConfig();
		virtual ~BufferConfig();

		void SetDefaults();

		void SetDefaultConstantBuffer(UINT byteWidth, bool isDynamic);
		void SetDefaultVertexBuffer(UINT byteWidth, bool isDynamic);
		void SetDefaultIndexBuffer(UINT byteWidth, bool isDynamic);
		// TODO: another buffer

		void SetByteWidht(UINT byteWidth);
		void SetUsage(D3D11_USAGE usage);
		void SetBindFlags(UINT bindFlags);
		void SetCPUAccessFlags(UINT CPUAccessFlags);
		void SetMiscFlags(UINT miscFlags);
		void SetStructrueByteStride(UINT structureByteStride);

		D3D11_BUFFER_DESC GetBufferDesc();

	protected:
		D3D11_BUFFER_DESC _state;
	};
}