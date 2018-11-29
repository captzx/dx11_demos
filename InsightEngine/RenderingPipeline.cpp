#include "pch.h"
#include "RenderingPipeline.h"

using namespace insight;

RenderingPipeline::RenderingPipeline(){

}

RenderingPipeline::~RenderingPipeline() {

}

void RenderingPipeline::SetDeviceContext(ID3D11DeviceContext* pDeviceContext) {
	_pDeviceContext = pDeviceContext;
}


void RenderingPipeline::ClearRenderTargetView(ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4]) {
	_pDeviceContext->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

void RenderingPipeline::OMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView *const *ppRenderTargetViews, ID3D11DepthStencilView *pDepthStencilView) {
	_pDeviceContext->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
}


void RenderingPipeline::RSSetViewports(UINT NumViewports, const D3D11_VIEWPORT *pViewports) {
	_pDeviceContext->RSSetViewports(NumViewports, pViewports);
}