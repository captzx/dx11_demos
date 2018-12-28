#include "pch.h"
#include "PipeResourceProxy.h"

#include "PipeBufferDesc.h"
#include "PipeViewDesc.h"
#include "PipeTextureDesc.h"

#include "Renderer.h"

using namespace insight;

PipeResourceProxy::PipeResourceProxy() {

}
PipeResourceProxy::PipeResourceProxy(int ResourceID, PipeBufferDesc* pDesc, Renderer* pRenderer, ShaderResourceViewDesc* pSRVDesc, RenderTargetViewDesc* pRTVDesc, UnorderedAccessViewDesc* pUAVDesc) {
	D3D11_BUFFER_DESC desc = pDesc->Get();
	_CreateViewByBindFlags(desc.BindFlags, ResourceID, pRenderer, pSRVDesc, pRTVDesc, pUAVDesc);

	_pBufferDesc = new PipeBufferDesc();
	*_pBufferDesc = *pDesc;
}
PipeResourceProxy::PipeResourceProxy(int ResourceID, Texture1dDesc* pDesc, Renderer* pRenderer, ShaderResourceViewDesc* pSRVDesc, RenderTargetViewDesc* pRTVDesc, UnorderedAccessViewDesc* pUAVDesc) {
	D3D11_TEXTURE1D_DESC desc = pDesc->Get();
	_CreateViewByBindFlags(desc.BindFlags, ResourceID, pRenderer, pSRVDesc, pRTVDesc, pUAVDesc);

	_pTexture1dDesc = new Texture1dDesc();
	*_pTexture1dDesc = *pDesc;
}

PipeResourceProxy::PipeResourceProxy(int ResourceID, Texture2dDesc* pDesc, Renderer* pRenderer, ShaderResourceViewDesc* pSRVDesc, RenderTargetViewDesc* pRTVDesc, UnorderedAccessViewDesc* pUAVDesc, DepthStencilViewDesc* pDSVDesc) {
	D3D11_TEXTURE2D_DESC desc = pDesc->Get();
	_CreateViewByBindFlags(desc.BindFlags, ResourceID, pRenderer, pSRVDesc, pRTVDesc, pUAVDesc);

	_pTexture2dDesc = new Texture2dDesc();
	*_pTexture2dDesc = *pDesc;
}
PipeResourceProxy::PipeResourceProxy(int ResourceID, Texture3dDesc* pDesc, Renderer* pRenderer, ShaderResourceViewDesc* pSRVDesc, RenderTargetViewDesc* pRTVDesc, UnorderedAccessViewDesc* pUAVDesc) {
	D3D11_TEXTURE3D_DESC desc = pDesc->Get();
	_CreateViewByBindFlags(desc.BindFlags, ResourceID, pRenderer, pSRVDesc, pRTVDesc, pUAVDesc);

	_pTexture3dDesc= new Texture3dDesc();
	*_pTexture3dDesc = *pDesc;
}

PipeResourceProxy::~PipeResourceProxy() {
	SAFE_DELETE(_pBufferDesc);
	SAFE_DELETE(_pTexture1dDesc);
	SAFE_DELETE(_pTexture2dDesc);
	SAFE_DELETE(_pTexture3dDesc);
	SAFE_DELETE(_pSRVDesc);
	SAFE_DELETE(_pRTVDesc);
	SAFE_DELETE(_pUAVDesc);
	SAFE_DELETE(_pDSVDesc);
}

void PipeResourceProxy::_CreateViewByBindFlags(UINT BindFlags, int ResourceID, Renderer* pRenderer, 
	ShaderResourceViewDesc* pSRVDesc, RenderTargetViewDesc* pRTVDesc, UnorderedAccessViewDesc* pUAVDesc, DepthStencilViewDesc* pDSVDesc) {
	_iResource = ResourceID;

	if (pSRVDesc) {
		_pSRVDesc = new ShaderResourceViewDesc();
		*_pSRVDesc = *pSRVDesc;
	}

	if (pRTVDesc) {
		pRTVDesc = new RenderTargetViewDesc();
		*_pRTVDesc = *pRTVDesc;
	}
	
	if (pUAVDesc) {
		_pUAVDesc = new UnorderedAccessViewDesc();
		*_pUAVDesc = *pUAVDesc;
	}
	
	if (pDSVDesc) {
		_pDSVDesc = new DepthStencilViewDesc();
		*_pDSVDesc = *pDSVDesc;
	}
/*
	if (BindFlags & D3D11_BIND_SHADER_RESOURCE == D3D11_BIND_SHADER_RESOURCE) {
		D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc = pSRVDesc ? &pSRVDesc->Get() : nullptr;
		_iResourceSRV = pRenderer->CreateShaderResourceView(_iResource, pDesc);
	}*/

	if ((BindFlags & D3D11_BIND_RENDER_TARGET) == D3D11_BIND_RENDER_TARGET) {
		D3D11_RENDER_TARGET_VIEW_DESC* pDesc = pRTVDesc ? &pRTVDesc->Get() : nullptr;
		_iResourceRTV = pRenderer->CreateRenderTargetView(_iResource, pDesc);
	}

	//if (BindFlags & D3D11_BIND_UNORDERED_ACCESS == D3D11_BIND_UNORDERED_ACCESS) {
	//	D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc = pUAVDesc ? &pUAVDesc->Get() : nullptr;
	//	_iResourceUAV = pRenderer->CreateUnorderedAccessView(_iResource, pDesc);
	//}

	if ((BindFlags & D3D11_BIND_DEPTH_STENCIL) == D3D11_BIND_DEPTH_STENCIL) {
		D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc = pDSVDesc ? &pDSVDesc->Get() : nullptr;
		_iResourceDSV = pRenderer->CreateDepthStencilView(_iResource, pDesc);
	}
}