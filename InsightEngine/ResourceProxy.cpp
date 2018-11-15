#include "pch.h"
#include "ResourceProxy.h"
#include "Texture2DConfig.h"
#include "Renderer.h"
#include "ShaderResourceViewConfig.h"
#include "RenderTargetViewConfig.h"
#include "BufferConfig.h"

using namespace insight;

ResourceProxy::ResourceProxy() {

}

ResourceProxy::ResourceProxy(int ResourceID, BufferConfig* pConfig, Renderer* pRenderer,
	ShaderResourceViewConfig* pSRVConfig = NULL,
	RenderTargetViewConfig* pRTVConfig = NULL/*,
	UnorderedAccessViewConfig* pUAVConfig = NULL,
	DepthStencilViewConfig* pDSVConfig = NULL*/){

}

ResourceProxy::ResourceProxy(int ResourceID, Texture2DConfig* pConfig, Renderer* pRenderer,
	ShaderResourceViewConfig* pSRVConfig = NULL,
	RenderTargetViewConfig* pRTVConfig = NULL/*,
	UnorderedAccessViewConfig* pUAVConfig = NULL,
	DepthStencilViewConfig* pDSVConfig = NULL*/) {

}
ResourceProxy::~ResourceProxy() {

}