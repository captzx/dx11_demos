#include "pch.h"
#include "RenderTargetView.h"

using namespace insight;

RenderTargetView::RenderTargetView(ID3D11RenderTargetView* pRenderTargetView) {
	_pRenderTargetView = pRenderTargetView;
}

RenderTargetView::~RenderTargetView() {

}

ID3D11RenderTargetView* RenderTargetView::Get() {
	return _pRenderTargetView;
}