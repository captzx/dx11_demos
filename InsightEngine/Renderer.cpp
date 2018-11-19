#include "pch.h"
#include "Renderer.h"

#include "BufferConfig.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

#include "PipelineManager.h"

#include "SwapChain.h"
#include "Texture2D.h"

#include "SwapChainConfig.h"
#include "Texture2DConfig.h"

#include "ResourceProxy.h"

#include "RenderTargetView.h"
#include "DepthStencilView.h"

#include "ViewPort.h"

#include "Texture2D.h"

using namespace insight;

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

std::shared_ptr <Renderer> Renderer::Get() {
	return _spRenderer;
}

std::shared_ptr<ResourceProxy> Renderer::CreateVertexBuffer(BufferConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData) {
	ID3D11Buffer* pBuffer;
	HRESULT hr = _pDevice->CreateBuffer(&pConfig->GetBufferDesc(), pData, &pBuffer);

	if (pBuffer) {
		VertexBuffer* pVertexBuffer = new VertexBuffer(pBuffer);
		pVertexBuffer->SetDesiredDescription(pConfig->GetBufferDesc());

		int ResourceID = StoreNewResource(pVertexBuffer);
		std::shared_ptr<ResourceProxy> Proxy(new ResourceProxy(ResourceID, pConfig, this));

		return Proxy;
	}

	return std::shared_ptr<ResourceProxy>(new ResourceProxy());
}

std::shared_ptr<ResourceProxy> Renderer::CreateIndexBuffer(BufferConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData) {
	ID3D11Buffer* pBuffer;
	HRESULT hr = _pDevice->CreateBuffer(&pConfig->GetBufferDesc(), pData, &pBuffer);

	if (pBuffer){
		IndexBuffer* pIndexBuffer = new IndexBuffer(pBuffer);
		pIndexBuffer->SetDesiredDescription(pConfig->GetBufferDesc());

		int ResourceID = StoreNewResource(pIndexBuffer);
		std::shared_ptr<ResourceProxy> Proxy(new ResourceProxy(ResourceID, pConfig, this));

		return Proxy;
	}

	return std::shared_ptr<ResourceProxy>(new ResourceProxy());
}

std::shared_ptr<ResourceProxy> Renderer::CreateConstantBuffer(BufferConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData, bool bAutoUpdate = true) {
	ID3D11Buffer* pBuffer;
	HRESULT hr = _pDevice->CreateBuffer(&pConfig->GetBufferDesc(), pData, &pBuffer);

	if (pBuffer) {
		ConstantBuffer* pConstantBuffer = new ConstantBuffer(pBuffer);
		pConstantBuffer->SetDesiredDescription(pConfig->GetBufferDesc());
		pConstantBuffer->SetAutoUpdate(bAutoUpdate);

		int ResourceID = StoreNewResource(pConstantBuffer);
		std::shared_ptr<ResourceProxy> Proxy(new ResourceProxy(ResourceID, pConfig, this));

		return Proxy;
	}

	return std::shared_ptr<ResourceProxy>(new ResourceProxy());
}

bool Renderer::Initialize(D3D_DRIVER_TYPE driverType, D3D_FEATURE_LEVEL featureLevel) {
	HRESULT hr = S_OK;

	IDXGIFactory* pFactory;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFactory));

	IDXGIAdapter* pCurrentAdapter;
	std::vector<IDXGIAdapter*> vpAdapters;
	while( pFactory->EnumAdapters(static_cast<UINT>(vpAdapters.size()), &pCurrentAdapter) != DXGI_ERROR_NOT_FOUND ){
		vpAdapters.push_back( pCurrentAdapter );

		DXGI_ADAPTER_DESC desc;
		pCurrentAdapter->GetDesc(&desc);
	}

	UINT CreateDeviceFlags = 0;
#ifdef _DEBUG
    CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	ID3D11DeviceContext* pContext;
	D3D_FEATURE_LEVEL level[] = { featureLevel };
	D3D_FEATURE_LEVEL createdLevel;
	if (DriverType == D3D_DRIVER_TYPE_HARDWARE){
		for (auto pAdapter : vpAdapters){
			hr = D3D11CreateDevice(
				pAdapter,
				D3D_DRIVER_TYPE_UNKNOWN,
				nullptr,
				CreateDeviceFlags,
				level,
				1,
				D3D11_SDK_VERSION,
				&_pDevice,
				&createdLevel,
				&pContext);

			if (hr == S_OK) break;
		}
	}
	else{
		hr = D3D11CreateDevice(
			nullptr,
			driverType,
			nullptr,
			CreateDeviceFlags,
			level,
			1,
			D3D11_SDK_VERSION,
			&_pDevice,
			&createdLevel,
			&pContext);
	}
	if (FAILED(hr)) {
		LOG(ERROR) << "D3D11CreateDevice";
		return false;
	}

	_featureLevel = createdLevel;

	_pImmPipeline = new PipelineManager();
	_pImmPipeline->SetDeviceContext(pContext, _featureLevel);

	D3D11_QUERY_DESC queryDesc;
	queryDesc.Query = D3D11_QUERY_PIPELINE_STATISTICS;
	queryDesc.MiscFlags = 0;

	for (int i = 0; i < PipelineManager::NumQueries; ++i){
		hr = _pDevice->CreateQuery(&queryDesc, &_pImmPipeline->_pQueries[i]);
		if (FAILED(hr)){
			LOG(ERROR) << "Unable to create a query object!";
			Shutdown();
			return(false);
		}
	}

	UINT uMassQuality;
	hr = _pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &uMassQuality);
	// assert(uMassQuality > 0);

	return hr;
}

void Renderer::Shutdown() {
	
}

int Renderer::CreateSwapChain(SwapChainConfig* pConfig) {
	HRESULT hr;

	IDXGIDevice* pDXGIDevice = nullptr;
	_pDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void **>(&pDXGIDevice));

	IDXGIAdapter* pDXGIAdapter = nullptr;
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void **>(&pDXGIAdapter));

	IDXGIFactory* pDXGIFactory = nullptr;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void **>(&pDXGIFactory));

	IDXGISwapChain* pSwapChain;
	hr = pDXGIFactory->CreateSwapChain(_pDevice, &pConfig->GetDesc(), &pSwapChain);
	if (FAILED(hr)) {
		LOG(ERROR) << "Failed to create swap chain!";
		return hr;
	}

	ID3D11Texture2D* pSwapChainBackBuffer;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void **>(&pSwapChainBackBuffer));
	if (FAILED(hr)) {
		LOG(ERROR) << "Failed to get swap chain texture resource!";
		return hr;
	}

	int ResourceID = StoreNewResource(new Texture2D(pSwapChainBackBuffer));

	Texture2DConfig textureConfig;
	pSwapChainBackBuffer->GetDesc(&textureConfig.GetDesc());

	std::shared_ptr<ResourceProxy> Proxy(new ResourceProxy(ResourceID, &textureConfig, this));

	_vSwapChains.push_back(new SwapChain(pSwapChain, Proxy));

	return(_vSwapChains.size() - 1);
}

std::shared_ptr<ResourceProxy> Renderer::GetSwapChainResource(int swapChainIndx) {
	if(swapChainIndx < _vSwapChains.size())
		return _vSwapChains[swapChainIndx]->GetResource();

	LOG(ERROR) << "Tried to get an invalid swap buffer index texture ID!";

	return std::shared_ptr<ResourceProxy>(new ResourceProxy());
}

int Renderer::StoreNewResource(Resource* pResource) {
	int index = GetUnusedResourceIndex();

	if (index == -1) {
		_vResources.push_back(pResource);
		index = _vResources.size() - 1;
	}
	else {
		_vResources[index] = pResource;
	}

	// Shift the inner ID to the upper 16 bits.
	int innerID = (int)pResource->GetInnerID() << 16;
	index = index + innerID;

	return(index);
}

int	Renderer::GetUnusedResourceIndex()
{
	// Initialize return index to -1.
	int index = -1;

	// Search for a NULL index location.
	for (unsigned int i = 0; i < _vResources.size(); i++) {
		if (_vResources[i] == NULL) {
			index = i;
			break;
		}
	}

	// Return either an empty location, or -1 if none exist.
	return(index);
}

void Renderer::Present(HWND hWnd = 0, int swapChain = -1, UINT SyncInterval = 0, UINT PresentFlags = 0) {
	unsigned int index = static_cast<unsigned int>(swapChain);

	if (index < _vSwapChains.size()) {
		SwapChain* pSwapChain = _vSwapChains[swapChain];
		HRESULT hr = pSwapChain->Get()->Present(SyncInterval, PresentFlags);
	}
	else {
		LOG(ERROR) << "Tried to present an invalid swap chain index!";
	}
}


int Renderer::CreateRenderTargetView(int ResourceID, D3D11_RENDER_TARGET_VIEW_DESC* pDesc) {
	ID3D11Resource* pRawResource;
	Resource* pResource = GetResourceByIndex(ResourceID);

	if (pResource) {
		pRawResource = pResource->GetResource();

		if (pRawResource) {
			ID3D11RenderTargetView* pRenderTargetView = nullptr;
			_pDevice->CreateRenderTargetView(pRawResource, pDesc, &pRenderTargetView);

			if (pRenderTargetView) {
				_vRenderTargetViews.push_back(pRenderTargetView);
				return _vRenderTargetViews.size()-1;
			}
		}
	}
}

int Renderer::CreateDepthStencilView(int ResourceID, D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc) {
	ID3D11Resource* pRawResource;
	Resource* pResource = GetResourceByIndex(ResourceID);

	if (pResource) {
		pRawResource = pResource->GetResource();

		if (pRawResource) {
			ID3D11DepthStencilView* pDepthStencilView = nullptr;
			_pDevice->CreateDepthStencilView(pRawResource, pDesc, &pDepthStencilView);

			if (pDepthStencilView) {
				_vDepthStencilViews.push_back(pDepthStencilView);
				return _vDepthStencilViews.size() - 1;
			}
		}
	}
}

Resource* Renderer::GetResourceByIndex(int id){
	Resource* pResource = 0;

	unsigned int index = id & 0xffff;
	int innerID = (id & 0xffff0000) >> 16;

	if (index < _vResources.size()) {
		pResource = _vResources[index];

		if (pResource->GetInnerID() != innerID) {
			LOG(ERROR) << "Inner ID doesn't match resource index!!!";
		}
	}

	return(pResource);
}

int Renderer::CreateViewPort(D3D11_VIEWPORT viewport) {
	_vViewPorts.emplace_back(viewport);
	return _vViewPorts.size() - 1;
}


int Renderer::CreateInputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>& elements, int ShaderID) {

}

std::shared_ptr<ResourceProxy> Renderer::CreateTexture2D(Texture2DConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData,
	ShaderResourceViewConfig* pSRVConfig,
	RenderTargetViewConfig* pRTVConfig,
	UnorderedAccessViewConfig* pUAVConfig,
	DepthStencilViewConfig* pDSVConfig) {

	ID3D11Texture2D* pTex = nullptr;
	_pDevice->CreateTexture2D(&pConfig->GetDesc(), pData, &pTex);

	if (pTex) {
		Texture2D* pTexture2D = new Texture2D(pTex);
		pTexture2D->SetDesiredDescription(pConfig->GetDesc());

		int resourceID = StoreNewResource(pTexture2D);
		std::shared_ptr<ResourceProxy> Proxy(new ResourceProxy(resourceID, pConfig, this, pSRVConfig, pRTVConfig));

		return Proxy;
	}

	return std::shared_ptr<ResourceProxy>(new ResourceProxy());
}

PipelineManager* Renderer::GetImmPipeline() {
	return _pImmPipeline;
}

int Renderer::LoadShader(ShaderType type, std::wstring& filename, std::wstring& function,
	std::wstring& model, bool enablelogging = true) {
	return LoadShader(type, filename, function, model, NULL, enablelogging);
}

int Renderer::LoadShader(ShaderType type, std::wstring& filename, std::wstring& function,
	std::wstring& model, const D3D_SHADER_MACRO* pDefines, bool enablelogging = true) {

}