#include "pch.h"
#include "DepthStencilView.h"

using namespace insight;

DepthStencilView::DepthStencilView(ID3D11DepthStencilView* pDepthStencilView) {
	_pDepthStencilView = pDepthStencilView;
}

DepthStencilView::~DepthStencilView() {

}

ID3D11DepthStencilView* DepthStencilView::Get() {
	return _pDepthStencilView;
}