#pragma once

namespace insight {
	class RenderTargetView {
	public:
		RenderTargetView(ComPtr<ID3D11RenderTargetView> pView);
		~RenderTargetView();

		ID3D11RenderTargetView* Get();

	protected:
		ComPtr<ID3D11RenderTargetView> _pRenderTargetView;
	};

	class DepthStencilView {
	public:
		DepthStencilView(ComPtr<ID3D11DepthStencilView> pView);
		~DepthStencilView();

		ID3D11DepthStencilView* Get();
	protected:
		ComPtr<ID3D11DepthStencilView> _pDepthStencilView;
	};
}