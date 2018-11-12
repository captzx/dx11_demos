#pragma once

namespace insight {
	class RenderTargetView {
	public:
		RenderTargetView(std::shared_ptr<RenderTargetView> pViewConfig);
		~RenderTargetView();

		ID3D11RenderTargetView* GetRTV();

	protected:
		std::shared_ptr<ID3D11RenderTargetView> _pRenderTargetView;
	};
}