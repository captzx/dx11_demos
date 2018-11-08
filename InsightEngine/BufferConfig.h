#pragma once

namespace insight {
	class BufferConfig {
	public:
		BufferConfig();
		virtual ~BufferConfig();

		D3D11_BUFFER_DESC GetBufferDesc();

	protected:
		D3D11_BUFFER_DESC _state;
	};
}