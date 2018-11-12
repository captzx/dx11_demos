#include "pch.h"
#include "ShaderResourceView.h"

using namespace insight;

ShaderResourceView::ShaderResourceView(std::shared_ptr<ShaderResourceView> pView) {
	_pShaderResourceView = pView;
}

ShaderResourceView::~ShaderResourceView() {

}

ID3D11ShaderResourceView* ShaderResourceView::GetSRV() {
	return _pShaderResourceView.get();
}