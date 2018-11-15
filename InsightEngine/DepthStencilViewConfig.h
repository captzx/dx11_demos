#pragma once

namespace insight {
	class DepthStencilViewConfig {
	public:
		DepthStencilViewConfig();
		~DepthStencilViewConfig();

		void SetDefaults();

		void SetFormat(DXGI_FORMAT format);
		void SetViewDimension(D3D11_DSV_DIMENSION viewDimension);
		void SetFlags(UINT flags);

		void SetTexture1D(D3D11_TEX1D_DSV texture1D);
		void SetTexture1DArray(D3D11_TEX1D_ARRAY_DSV texture1DArray);
		void SetTexture2D(D3D11_TEX2D_DSV texture2D);
		void SetTexture2DArray(D3D11_TEX2D_ARRAY_DSV texture2DArray);
		void SetTexture2DMS(D3D11_TEX2DMS_DSV texture2DMS);
		void SetTexture2DMSArray(D3D11_TEX2DMS_ARRAY_DSV texture2DMSArray);

		D3D11_DEPTH_STENCIL_VIEW_DESC& GetDesc();

	protected:
		D3D11_DEPTH_STENCIL_VIEW_DESC _state;
	};
}