#pragma once

namespace insight {
	class DepthStencilView {
	public:
		DepthStencilView(ID3D11DepthStencilView* pDepthStencilView);
		~DepthStencilView();

		ID3D11DepthStencilView* Get();

	protected:
		ID3D11DepthStencilView* _pDepthStencilView;
	};
}