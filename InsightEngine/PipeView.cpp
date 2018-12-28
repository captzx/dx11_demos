#include "pch.h"
#include "PipeView.h"

using namespace insight;

RenderTargetView::RenderTargetView(ComPtr<ID3D11RenderTargetView> pView):_pRenderTargetView(pView){

}
RenderTargetView::~RenderTargetView() {

}

ID3D11RenderTargetView* RenderTargetView::Get() {
	return _pRenderTargetView.Get();
}



//##################################


DepthStencilView::DepthStencilView(ComPtr<ID3D11DepthStencilView> pView):_pDepthStencilView(pView) {

}
DepthStencilView::~DepthStencilView() {

}

ID3D11DepthStencilView* DepthStencilView::Get() {
	return _pDepthStencilView.Get();
}