#pragma once

namespace insight{
	class Texture2DConfig {
	public:
		Texture2DConfig();
		virtual ~Texture2DConfig();

		void SetDefaults();
		void SetDepthBuffer(UINT width, UINT height);
		void SetColorBuffer(UINT width, UINT height);

		void SetWidth(UINT width);
		void SetHeight(UINT height);
		void SetMipLevels(UINT mipLevels);
		void SetArraySize(UINT arraySize);
		void SetFormat(DXGI_FORMAT format);
		void SetSampleDesc(DXGI_SAMPLE_DESC sampleDesc);
		void SetUsage(D3D11_USAGE usage);
		void SetBindFlags(UINT bindFlags);
		void SetCPUAccessFlags(UINT CPUAccessFlags);
		void SetMiscFlags(UINT miscFlags);

		D3D11_TEXTURE2D_DESC GetDesc();

	protected:
		D3D11_TEXTURE2D_DESC _state;
	};
}