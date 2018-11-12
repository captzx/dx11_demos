#pragma once

namespace insight {
	class ShaderResourceViewConfig {
	public:
		ShaderResourceViewConfig();
		~ShaderResourceViewConfig();

		void SetDefaults();

		void SetFormat(DXGI_FORMAT format);
		void SetViewDimension(D3D11_SRV_DIMENSION viewDimension);

		void SetBuffer(D3D11_BUFFER_SRV buffer);
		void SetTexture1D(D3D11_TEX1D_SRV texture1D);
		void SetTexture1DArray(D3D11_TEX1D_ARRAY_SRV texture1DArray);
		void SetTexture2D(D3D11_TEX2D_SRV texture2D);
		void SetTexture2DArray(D3D11_TEX2D_ARRAY_SRV texture2DArray);
		void SetTexture2DMS(D3D11_TEX2DMS_SRV texture2DMS);
		void SetTexture2DMSArray(D3D11_TEX2DMS_ARRAY_SRV texture2DMSArray);
		void SetTexture3D(D3D11_TEX3D_SRV texture3D);

		D3D11_SHADER_RESOURCE_VIEW_DESC& GetSRVDesc();

	protected:
		D3D11_SHADER_RESOURCE_VIEW_DESC _state;
	};
}