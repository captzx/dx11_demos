#include "pch.h"
#include "RenderTargetView.h"

using namespace insight;

RenderTargetView::RenderTargetView(std::shared_ptr<RenderTargetView> pView) {
	_pRenderTargetView = pView;
}

RenderTargetView::~RenderTargetView() {

}

ID3D11RenderTargetView* RenderTargetView::GetRTV() {
	return _pRenderTargetView.get();
}