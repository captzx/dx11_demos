#pragma once

namespace insight {
	enum ResourceType
	{
		RT_VERTEXBUFFER = 0x010000,
		RT_INDEXBUFFER = 0x020000,
		RT_CONSTANTBUFFER = 0x030000,
		RT_STRUCTUREDBUFFER = 0x040000,
		RT_BYTEADDRESSBUFFER = 0x050000,
		RT_INDIRECTARGSBUFFER = 0x060000,
		RT_TEXTURE1D = 0x070000,
		RT_TEXTURE2D = 0x080000,
		RT_TEXTURE3D = 0x090000
	};

	class Buffer;
	class VertexBuffer;
	class IndexBuffer;

	class BufferConfig;

	class Renderer {
	public:
		Renderer();
		virtual ~Renderer();

		std::shared_ptr<ID3D11Device> GetDevice() { return _pDevice; }

		void CreateVertexBuffer(BufferConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData);
	protected:
		std::shared_ptr<ID3D11Device> _pDevice;

	};
}