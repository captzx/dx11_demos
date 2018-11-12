#pragma once

namespace insight {
	class RenderTargetViewConfig {
	public:
		RenderTargetViewConfig();
		~RenderTargetViewConfig();

		void SetDefaults();

		void SetFormat(DXGI_FORMAT format);
		void SetViewDimension(D3D11_RTV_DIMENSION viewDimension);

		void SetBuffer(D3D11_BUFFER_RTV buffer);
		void SetTexture1D(D3D11_TEX1D_RTV texture1D);
		void SetTexture1DArray(D3D11_TEX1D_ARRAY_RTV texture1DArray);
		void SetTexture2D(D3D11_TEX2D_RTV texture2D);
		void SetTexture2DArray(D3D11_TEX2D_ARRAY_RTV texture2DArray);
		void SetTexture2DMS(D3D11_TEX2DMS_RTV texture2DMS);
		void SetTexture2DMSArray(D3D11_TEX2DMS_ARRAY_RTV texture2DMSArray);
		void SetTexture3D(D3D11_TEX3D_RTV texture3D);

		D3D11_RENDER_TARGET_VIEW_DESC& GetRTVDesc();

	protected:
		D3D11_RENDER_TARGET_VIEW_DESC _state;
	};
}