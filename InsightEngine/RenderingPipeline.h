#pragma once

namespace insight {
	class RenderingPipeline {
	public:
		RenderingPipeline();
		~RenderingPipeline();

	public:
		void SetDeviceContext(ID3D11DeviceContext*  pDeviceContext);

		void ClearRenderTargetView(ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4]);
		void OMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView *const *ppRenderTargetViews, ID3D11DepthStencilView *pDepthStencilView);

		void RSSetViewports(UINT NumViewports,const D3D11_VIEWPORT *pViewports);
	private:
		ComUniquePtr<ID3D11DeviceContext>  _pDeviceContext;
	};

}