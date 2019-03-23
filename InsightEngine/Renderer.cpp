#include "pch.h"
#include "Renderer.h"

#include "RenderingPipeline.h"
#include "SwapChain.h"

#include "Shader.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "ShaderReflection.h"

#include "PipeBufferDesc.h"
#include "PipeTextureDesc.h"
#include "PipeViewDesc.h"
#include "PipeBuffer.h"
#include "PipeTexture.h"
#include "PipeResource.h"
#include "PipeView.h"

#include "ViewPort.h"

#include "ParameterManager.h"
using namespace insight;

Renderer* Renderer::_spRenderer = nullptr;

Renderer::Renderer():
	_pImmPipeline(new RenderingPipeline()),
	_pParameterManager(new ParameterManager(0)){
	_spRenderer = this;
}
Renderer::~Renderer() {
	Shutdown();
}

Renderer* Renderer::Get(){
	return _spRenderer;
}

bool Renderer::Initialize(D3D_DRIVER_TYPE driverType, D3D_FEATURE_LEVEL featureLevel) {
	HRESULT hr = S_OK;

	IDXGIFactory* pFactory;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));

	UINT i = 0;
	IDXGIAdapter * pAdapter;
	std::vector <IDXGIAdapter*> vAdapters;
	while (pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND){
		vAdapters.push_back(pAdapter);
		++i;
	}

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL levels[] = { featureLevel };
	D3D_FEATURE_LEVEL createdLevel;
	ID3D11DeviceContext* pDeviceContext = nullptr;
	if (DriverType == D3D_DRIVER_TYPE_HARDWARE) {
		for (auto pAdapter : vAdapters) {
			hr = D3D11CreateDevice(pAdapter, D3D_DRIVER_TYPE_UNKNOWN, nullptr, createDeviceFlags, levels, 1, D3D11_SDK_VERSION,
				&_pDevice, &createdLevel, &pDeviceContext);
			if (hr == S_OK) break;
		}
	}
	else {
		hr = D3D11CreateDevice(
			nullptr/*default adapter*/, driverType, nullptr, createDeviceFlags, levels, 1, D3D11_SDK_VERSION,
			&_pDevice, &createdLevel, &pDeviceContext);
	}

	if (FAILED(hr)) {
		// log
		return false;
	}
	else {
		_pImmPipeline->SetDeviceContext(pDeviceContext);
	}

	_pRenderTargetViews.emplace_back(ComPtr<ID3D11RenderTargetView>());
	_pDepthStencilViews.emplace_back(ComPtr<ID3D11DepthStencilView>());

	UINT uMassQuality;
	hr = _pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &uMassQuality);

	return hr;
}
void Renderer::Shutdown() {
	SAFE_DELETE(_pParameterManager);
	SAFE_DELETE(_pImmPipeline);

	for (auto pResource : _pPipeResources)
		delete pResource;

	for (auto pSwapChain : _vSwapChains) {
		if (pSwapChain->Get() != nullptr) {
			pSwapChain->Get()->SetFullscreenState(false, NULL);
		}
		delete pSwapChain;
	}
	for (auto pShader : _pShaders)
		delete pShader;
}

int Renderer::CreateSwapChain(const SwapChainDesc& SCD) {
	HRESULT hr = S_OK;

	ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
	_pDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void **>(pDXGIDevice.GetAddressOf()));

	ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void **>(pDXGIAdapter.GetAddressOf()));

	ComPtr<IDXGIFactory> pDXGIFactory = nullptr;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void **>(pDXGIFactory.GetAddressOf()));
	
	ComPtr<IDXGISwapChain> pSwapChain;
	hr = pDXGIFactory->CreateSwapChain(_pDevice.Get(), &SCD.Get(), &pSwapChain);
	if (hr) {
		//log
	}

	ComPtr<ID3D11Texture2D> pSwapChainBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(pSwapChainBuffer.GetAddressOf()));
	int ResourceID = _StoreNewResource(new Texture2D(pSwapChainBuffer));

	Texture2dDesc TextureDesc;
	pSwapChainBuffer->GetDesc(&TextureDesc.Get());

	std::shared_ptr<PipeResourceProxy> Proxy(new PipeResourceProxy(ResourceID, &TextureDesc, this));

	_vSwapChains.push_back(new SwapChain(pSwapChain, Proxy));
	return _vSwapChains.size() - 1;
}

std::shared_ptr<PipeResourceProxy> Renderer::CreateTexture2D(Texture2dDesc* pConfig, D3D11_SUBRESOURCE_DATA* pData,
	ShaderResourceViewDesc* pSRVConfig,
	RenderTargetViewDesc* pRTVConfig,
	UnorderedAccessViewDesc* pUAVConfig,
	DepthStencilViewDesc* pDSVConfig) {
	ComPtr<ID3D11Texture2D> pTexture;
	HRESULT hr = _pDevice->CreateTexture2D(&pConfig->Get(), pData, &pTexture);

	if (pTexture){
		Texture2D* pTex = new Texture2D(pTexture);
		pTex->SetDesiredDescription(pConfig->Get());

		int ResourceID = _StoreNewResource(pTex);
		std::shared_ptr<PipeResourceProxy> Proxy(new PipeResourceProxy(ResourceID, pConfig, this));

		return(Proxy);
	}

	return(std::shared_ptr<PipeResourceProxy>(new PipeResourceProxy()));
}

int Renderer::CreateRenderTargetView(int ResourceID, D3D11_RENDER_TARGET_VIEW_DESC* pDesc) {
	ID3D11Resource* pRawResource = nullptr;
	PipeResource* pResource = _GetResourceByIndex(ResourceID);

	if (pResource) {
		pRawResource = pResource->GetResource();

		if (pRawResource) {
			ComPtr<ID3D11RenderTargetView> pView;
			HRESULT hr = _pDevice->CreateRenderTargetView(pRawResource, pDesc, &pView);

			if (pView) {
				_pRenderTargetViews.push_back(pView);
				return _pRenderTargetViews.size() - 1;
			}
		}
	}

	return -1;
}
int Renderer::CreateDepthStencilView(int ResourceID, D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc) {
	ID3D11Resource* pRawResource = nullptr;
	PipeResource* pResource = _GetResourceByIndex(ResourceID);

	if (pResource) {
		pRawResource = pResource->GetResource();

		if (pRawResource) {
			ComPtr<ID3D11DepthStencilView> pView;
			HRESULT hr = _pDevice->CreateDepthStencilView(pRawResource, pDesc, &pView);

			if (pView) {
				_pDepthStencilViews.push_back(pView);
				return _pDepthStencilViews.size() - 1;
			}
		}
	}

	return -1;
}

int Renderer::CreateInputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>& elements, int ShaderID) {
	D3D11_INPUT_ELEMENT_DESC* pElements = new D3D11_INPUT_ELEMENT_DESC[elements.size()];
	for (unsigned int i = 0; i < elements.size(); i++)
		pElements[i] = elements[i];

	ID3DBlob* pCompiledShader = _pShaders[ShaderID]->GetCompiledShader();
	ID3D11InputLayout* pLayout;

	HRESULT hr = _pDevice->CreateInputLayout(pElements, 2, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &pLayout);

 	if (FAILED(hr)){
		return(-1);
	}

	_pInputLayouts.push_back(pLayout);

	SAFE_DELETE(pElements);

	return(_pInputLayouts.size() - 1);
}

int Renderer::LoadShader(ShaderType type, LPCWSTR fileName, _In_ LPCSTR entryFunc, _In_ LPCSTR model){
	for (size_t i = 0; i < _pShaders.size(); ++i) {
		Shader* pShader = _pShaders[i];

		if (pShader->IsExist(fileName, entryFunc, model)) {
			return i;
		}
	}

	HRESULT hr = S_OK;

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrorMessages = nullptr;
	hr = D3DCompileFromFile(fileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryFunc, model, flags, NULL, &pCompiledShader, &pErrorMessages);
	if (!pCompiledShader) {
		OutputDebugStringA((char*)pErrorMessages->GetBufferPointer());
	}

	Shader* pShaderWrapper = nullptr;
	switch (type) {
		case VERTEX_SHADER:
		{
			ID3D11VertexShader* pShader = 0;

			hr = _pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), 0, &pShader);

			pShaderWrapper = new VertexShader(pShader);
			break;
		}
		case PIXEL_SHADER:
		{
			ID3D11PixelShader* pShader = 0;

			hr = _pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), 0, &pShader);

			pShaderWrapper = new PixelShader(pShader);
			break;
		}
		default:
			break;
	}

	if (FAILED(hr)) {
		pCompiledShader->Release();
		
		return -1;
	}

	pShaderWrapper->Set(fileName, entryFunc, model);

	_pShaders.push_back(pShaderWrapper);
	pShaderWrapper->SetCompiledShader(pCompiledShader);

	ShaderReflection* pReflection = ShaderReflectionFactory::GenerateReflection(*pShaderWrapper);

	pReflection->InitializeConstantBuffers(_pParameterManager);

	pShaderWrapper->SetReflection(pReflection);

	return _pShaders.size() - 1;
}

std::shared_ptr<PipeResourceProxy> Renderer::CreateVertexBuffer(PipeBufferDesc* pDesc, D3D11_SUBRESOURCE_DATA* pData) {
	ComPtr<ID3D11Buffer> pvb = nullptr;

	HRESULT hr = _pDevice->CreateBuffer(&pDesc->Get(), pData, &pvb);

	if (pvb) {
		VertexBuffer* pVertexBuffer = new VertexBuffer(pvb);
		pVertexBuffer->SetDesiredDescription(pDesc->Get());

		int ResourceID = _StoreNewResource(pVertexBuffer);
		std::shared_ptr<PipeResourceProxy> Proxy(new PipeResourceProxy(ResourceID, pDesc, this));

		return(Proxy);
	}

	return std::shared_ptr<PipeResourceProxy>();
}
std::shared_ptr<PipeResourceProxy> Renderer::CreateIndexBuffer(PipeBufferDesc* pDesc, D3D11_SUBRESOURCE_DATA* pData) {
	ComPtr<ID3D11Buffer> pib = nullptr;

	HRESULT hr = _pDevice->CreateBuffer(&pDesc->Get(), pData, &pib);

	if (pib) {
		IndexBuffer* pIndexBuffer = new IndexBuffer(pib);
		pIndexBuffer->SetDesiredDescription(pDesc->Get());

		int ResourceID = _StoreNewResource(pIndexBuffer);
		std::shared_ptr<PipeResourceProxy> Proxy(new PipeResourceProxy(ResourceID, pDesc, this));

		return(Proxy);
	}

	return std::shared_ptr<PipeResourceProxy>();
}
std::shared_ptr<PipeResourceProxy> Renderer::CreateConstantBuffer(PipeBufferDesc * pDesc, D3D11_SUBRESOURCE_DATA * pData, bool bAutoUpdate){
	ComPtr<ID3D11Buffer> pcb = nullptr;
	HRESULT hr = _pDevice->CreateBuffer(&pDesc->Get(), pData, &pcb);

	if (pcb){
		ConstantBuffer* pConstantBuffer = new ConstantBuffer(pcb);
		pConstantBuffer->SetDesiredDescription(pDesc->Get());

		int ResourceID = _StoreNewResource(pConstantBuffer);
		std::shared_ptr<PipeResourceProxy> Proxy(new PipeResourceProxy(ResourceID, pDesc, this));

		return(Proxy);
	}

	return(std::shared_ptr<PipeResourceProxy>(new PipeResourceProxy()));
}

int Renderer::CreateViewPort(D3D11_VIEWPORT viewport){
	_vViewPorts.emplace_back(viewport);

	return(_vViewPorts.size() - 1);
}

void Renderer::Present(HWND hWnd, int SwapChainID, UINT SyncInterval, UINT PresentFlags){
	unsigned int index = static_cast<unsigned int>(SwapChainID);

	if (index < _vSwapChains.size()) {
		SwapChain* pSwapChain = _vSwapChains[SwapChainID];
		HRESULT hr = pSwapChain->Get()->Present(SyncInterval, PresentFlags);
	}
	else {
		
	}
}

Shader* Renderer::GetShader(size_t index){
	if (index < _pShaders.size()) {
		return _pShaders[index];
	}

	return nullptr;
}

const ViewPort& Renderer::GetViewPort(int ID){
	unsigned int index = static_cast<unsigned int>(ID);
	assert(index < _vViewPorts.size());

	return(_vViewPorts[index]);
}
PipeResource* Renderer::GetResourceByIndex(int rid){
	return _GetResourceByIndex(rid);
}
// ---------------------------------get----------------------------------
Texture2D* Renderer::GetTexture2DByIndex(int rid) {
	Texture2D* pResult = 0;

	PipeResource* pResource = _GetResourceByIndex(rid);

	if (pResource != NULL) {
		if (pResource->GetType() != PRT_TEXTURE2D) {
			
		}
		else {
			pResult = reinterpret_cast<Texture2D*>(pResource);
		}
	}

	return(pResult);
}

std::shared_ptr<PipeResourceProxy> Renderer::GetSwapChainResource(int ID){
	unsigned int index = static_cast<unsigned int>(ID);

	if (index < _vSwapChains.size())
		return(_vSwapChains[index]->GetBuffer());

	//Log::Get().Write(L"Tried to get an invalid swap buffer index texture ID!");

	return(std::shared_ptr<PipeResourceProxy>(new PipeResourceProxy()));
}

//ConstantBuffer*	Renderer::GetConstantBufferByIndex(int rid) {
//	ConstantBuffer* pResult = 0;
//
//	PipeResource* pResource = _GetResourceByIndex(rid);
//
//	if (pResource != NULL) {
//		if (pResource->GetType() != PRT_CONSTANTBUFFER) {
//		}
//		else {
//			pResult = reinterpret_cast<ConstantBuffer*>(pResource);
//		}
//	}
//
//	return(pResult);
//}
VertexBuffer* Renderer::GetVertexBufferByIndex(int rid) {
	VertexBuffer* pResult = 0;

	PipeResource* pResource = _GetResourceByIndex(rid);

	if (pResource != NULL) {
		if (pResource->GetType() != PRT_VERTEXBUFFER) {
		}
		else {
			pResult = reinterpret_cast<VertexBuffer*>(pResource);
		}
	}

	return(pResult);
}
IndexBuffer* Renderer::GetIndexBufferByIndex(int rid) {
	IndexBuffer* pResult = 0;

	PipeResource* pResource = _GetResourceByIndex(rid);

	if (pResource != NULL) {
		if (pResource->GetType() != PRT_INDEXBUFFER) {
		}
		else {
			pResult = reinterpret_cast<IndexBuffer*>(pResource);
		}
	}

	return pResult;
}
ConstantBuffer* Renderer::GetConstantBufferByIndex(int rid){
	ConstantBuffer* pResult = 0;

	PipeResource* pResource = _GetResourceByIndex(rid);

	if (pResource != NULL) {
		if (pResource->GetType() != PRT_CONSTANTBUFFER) {
		}
		else {
			pResult = reinterpret_cast<ConstantBuffer*>(pResource);
		}
	}

	return pResult;
}
//ConstantBuffer* Renderer::GetConstantBufferByIndex(int rid) {
//	ConstantBuffer* pResult = 0;
//
//	PipeResource* pResource = _GetResourceByIndex(rid);
//
//	if (pResource != NULL) {
//		if (pResource->GetType() != PRT_INDEXBUFFER) {
//		}
//		else {
//			pResult = reinterpret_cast<ConstantBuffer*>(pResource);
//		}
//	}
//
//	return pResult;
//}
RenderTargetView& Renderer::GetRenderTargetViewByIndex(int rid) {
	return _pRenderTargetViews[rid];
}


DepthStencilView& Renderer::GetDepthStencilViewByIndex(int rid) {
	return _pDepthStencilViews[rid];
}
ComPtr<ID3D11InputLayout> Renderer::GetInputLayout(size_t index){
	if (index <= _pInputLayouts.size()) {
		return _pInputLayouts[index];
	}
	return nullptr;
}

int	Renderer::_GetUnusedResourceIndex(){
	int index = -1;

	for (unsigned int i = 0; i < _pPipeResources.size(); i++) {
		if (_pPipeResources[i] == NULL) {
			index = i;
			break;
		}
	}

	return index;
}
int	Renderer::_StoreNewResource(PipeResource* pResource){
	int index = _GetUnusedResourceIndex();

	if (index == -1) {
		_pPipeResources.push_back(pResource);
		index = _pPipeResources.size() - 1;
	}
	else {
		_pPipeResources[index] = pResource;
	}

	int innerID = (int)pResource->GetUID() << 16;
	index = index + innerID;

	return index;
}

PipeResource* Renderer::_GetResourceByIndex(int ID){
	PipeResource* pResource = 0;

	unsigned int index = ID & 0xffff;
	int innerID = (ID & 0xffff0000) >> 16;

	if (index < _pPipeResources.size()) {
		pResource = _pPipeResources[index];

		if (pResource->GetUID() != innerID) {
			
		}
	}

	return pResource;
}