#include "pch.h"
#include "Renderer.h"
#include "BufferConfig.h"
#include "VertexBuffer.h"
#include "PipelineManager.h"
#include "SwapChainConfig.h"

using namespace insight;

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

std::shared_ptr <Renderer> Renderer::Get() {
	return _spRenderer;
}

std::shared_ptr<Resource> Renderer::CreateVertexBuffer(BufferConfig* pConfig, D3D11_SUBRESOURCE_DATA* pData) {
	
}

bool Renderer::Initialize(D3D_DRIVER_TYPE driverType, D3D_FEATURE_LEVEL featureLevel) {
	HRESULT hr = S_OK;

	IDXGIFactory* pFactory;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFactory));

	IDXGIAdapter* pCurrentAdapter;
	std::vector<IDXGIAdapter*> vAdapters;

	while( pFactory->EnumAdapters( static_cast<UINT>(vAdapters.size()), &pCurrentAdapter) != DXGI_ERROR_NOT_FOUND ){
		vAdapters.push_back( pCurrentAdapter );

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
		for (auto pAdapter : vAdapters){
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

			if (hr == S_OK)
				break;
		}
	}
	else
	{
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

	// Grab a copy of the feature level for use by the rest of the rendering system.
	_featureLevel = _pDevice->GetFeatureLevel();

	// Create the renderer components here, including the parameter manager, pipeline manager, and resource manager.

	//_pParamMgr = new ParameterManager(0);
	_pImmPipeline = new PipelineManager();
	_pImmPipeline->SetDeviceContext(pContext, _featureLevel);

	// Rasterizer State (RS) - the first state will be index zero, so no need
	// to keep a copy of it here.

	RasterizerStateConfig RasterizerState;
	_pImmPipeline->RasterizerStage.DesiredState.RasterizerState.SetState(CreateRasterizerState(&RasterizerState));

	// Depth Stencil State (DS) - the first state will be index zero, so no need
	// to keep a copy of it here.

	DepthStencilStateConfig DepthStencilState;
	_pImmPipeline->OutputMergerStage.DesiredState.DepthStencilState.SetState(CreateDepthStencilState(&DepthStencilState));

	// Output Merger State (OM) - the first state will be index zero, so no need
	// to keep a copy of it here.

	BlendStateConfig BlendState;
	_pImmPipeline->OutputMergerStage.DesiredState.BlendState.SetState(CreateBlendState(&BlendState));


	// Create the default resource views for each category.  This has the effect
	// of allowing the '0' index to be the default state.

	_vShaderResourceViews.emplace_back(ShaderResourceViewComPtr());
	_vUnorderedAccessViews.emplace_back(UnorderedAccessViewComPtr());
	_vRenderTargetViews.emplace_back(RenderTargetViewComPtr());
	_vDepthStencilViews.emplace_back(DepthStencilViewComPtr());


	// Create a query object to be used to gather statistics on the pipeline.

	D3D11_QUERY_DESC queryDesc;
	queryDesc.Query = D3D11_QUERY_PIPELINE_STATISTICS;
	queryDesc.MiscFlags = 0;

	for (int i = 0; i < PipelineManager::NumQueries; ++i)
	{
		hr = _pDevice->CreateQuery(&queryDesc, &_pImmPipeline->_pQueries[i]);

		if (FAILED(hr))
		{
			//Log::Get().Write(L"Unable to create a query object!");
			Shutdown();
			return(false);
		}
	}

	UINT NumQuality;
	HRESULT hr1 = _pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &NumQuality);

	return hr;
}

void Renderer::Shutdown() {
	// state.clear()
	// safe_release()
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
	hr = pDXGIFactory->CreateSwapChain(_pDevice, &pConfig->_state, &pSwapChain);

	if (FAILED(hr)) {
		LOG(ERROR) << "Failed to create swap chain!";
		return hr;
	}

	ID3D11Texture2D* pSwapChainBuffer;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void **>(&pSwapChainBuffer));//获得SwapChain中后台缓存 COM组件:pSwapChainBuffer

	if (FAILED(hr)) {
		LOG(ERROR) << "Failed to get swap chain texture resource!";
		return hr;
	}

	int ResourceID = StoreNewResource(new Texture2D(pSwapChainBuffer));

	// If we get here, then we succeeded in creating our swap chain and it's constituent parts.
	// Now we create the wrapper object and store the result in our container.

	Texture2dConfig TextureConfig;
	pSwapChainBuffer->GetDesc(&TextureConfig.m_State);

	Resource* Proxy(new ResourceProxy(ResourceID, &TextureConfig, this));
	// With the resource proxy created, create the swap chain wrapper and store it.
	// The resource proxy can then be used later on by the application to get the
	// RTV or texture ID if needed.

	_vSwapChains.push_back(new SwapChain(pSwapChain, Proxy));

	return(_vSwapChains.size() - 1);
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
		HRESULT hr = pSwapChain->_pSwapChain->Present(SyncInterval, PresentFlags);
	}
	else {
		LOG(ERROR) << "Tried to present an invalid swap chain index!";
	}
}
