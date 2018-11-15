#pragma once

namespace insight {
	class RenderTargetView {
	public:
		RenderTargetView(ID3D11RenderTargetView* pRenderTargetView);
		~RenderTargetView();

		ID3D11RenderTargetView* Get();

	protected:
		ID3D11RenderTargetView* _pRenderTargetView;
	};
}