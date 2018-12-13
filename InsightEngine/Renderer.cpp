#include "pch.h"
#include "Renderer.h"
#include "RenderingPipeline.h"
#include "SwapChain.h"
#include "Application.h"
#include "Window.h"
#include "Shader.h"
#include "VertexShader.h"
#include "PixelShader.h"
using namespace insight;

Renderer* _spRenderer = nullptr;

Renderer::Renderer():
	_pImmPipeline(new RenderingPipeline()){
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

	UINT uMassQuality;
	hr = _pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &uMassQuality);

	return hr;
}
void Renderer::Shutdown() {
	SAFE_DELETE(_pImmPipeline);
	SAFE_RELEASE(_pSwapChain);
	SAFE_RELEASE(_pBackBuffer);
	SAFE_RELEASE(_pRenderTargetView);
	SAFE_RELEASE(_pDepthStencilView);
	SAFE_RELEASE(_pDevice);
}

bool Renderer::CreateSwapChain(const SwapChainDesc& swapChainDesc) {
	HRESULT hr = S_OK;

	IDXGIDevice* pDXGIDevice = nullptr;
	_pDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void **>(&pDXGIDevice));

	IDXGIAdapter* pDXGIAdapter = nullptr;
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void **>(&pDXGIAdapter));

	IDXGIFactory* pDXGIFactory = nullptr;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void **>(&pDXGIFactory));

	hr = pDXGIFactory->CreateSwapChain(_pDevice, &swapChainDesc.Get(), &_pSwapChain);
	if (hr) {
		//log
	}

	_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&_pBackBuffer));
	_pBackBuffer->GetDesc(&_BackBufferDesc);
	return hr;
}

bool Renderer::CreateTexture2D() {
	HRESULT hr = S_OK;
	// _pDevice->CreateTexture2D()
	return hr;
}

bool Renderer::CreateRenderTargetView() {
	HRESULT hr = S_OK;

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = DXGI_FORMAT_UNKNOWN;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_UNKNOWN;
	hr = _pDevice->CreateRenderTargetView(_pBackBuffer, 0, &_pRenderTargetView);
	if (!hr) {
		// log
	}

	return hr;
}


bool Renderer::CreateDepthStencilView() {

	D3D11_TEXTURE2D_DESC tex2ddesc;
	tex2ddesc.Width = 800;
	tex2ddesc.Height = 600;
	tex2ddesc.MipLevels = 1;
	tex2ddesc.ArraySize = 1;
	tex2ddesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex2ddesc.SampleDesc.Count = 1;
	tex2ddesc.SampleDesc.Quality = 0;
	tex2ddesc.Usage = D3D11_USAGE_DEFAULT;
	tex2ddesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex2ddesc.CPUAccessFlags = 0;
	tex2ddesc.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencilBuff;
	_pDevice->CreateTexture2D(&tex2ddesc, 0, &pDepthStencilBuff);
	auto hr = _pDevice->CreateDepthStencilView(pDepthStencilBuff,0,&_pDepthStencilView);

	return hr;
}

int insight::Renderer::CreateInputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>& elements, int ShaderID){
	D3D11_INPUT_ELEMENT_DESC* pElements = new D3D11_INPUT_ELEMENT_DESC[elements.size()];
	for (unsigned int i = 0; i < elements.size(); i++)
		pElements[i] = elements[i];

	ID3DBlob* pCompiledShader = _vpShaders[ShaderID]->GetCompiledShader();
	ID3D11InputLayout* pLayout;

	HRESULT hr = _pDevice->CreateInputLayout(pElements, elements.size(),
		pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &pLayout);

	delete[] pElements;

	if (FAILED(hr)){
		return(-1);
	}

	_vpInputLayouts.push_back(pLayout);

	return(_vpInputLayouts.size() - 1);
}

int insight::Renderer::LoadShader(ShaderType type, std::wstring fileName, std::string entryFunc, std::string model){
	for (size_t i = 0; i < _vpShaders.size(); ++i) {
		Shader* pShader = _vpShaders[i];

		if (pShader->IsExist(fileName, entryFunc, model)) {
			return i;
		}
	}

	HRESULT hr = S_OK;

	UINT flags = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
#ifdef _DEBUG
	flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrorMessages = nullptr;
	hr = D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, 
		entryFunc.c_str(), model.c_str(), flags, NULL, &pCompiledShader, &pErrorMessages);

	if (!pCompiledShader) {
		return -1;
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
	}

	if (FAILED(hr)) {
		pCompiledShader->Release();
		
		return -1;
	}

	pShaderWrapper->Set(fileName, entryFunc, model);

	_vpShaders.push_back(pShaderWrapper);
	pShaderWrapper->SetCompiledShader(pCompiledShader);

	return _vpShaders.size() - 1;
}

void Renderer::Present() {
	_pSwapChain->Present(0, 0);
}


Shader* insight::Renderer::GetShader(int index){
	if (index < _vpShaders.size()) {
		return _vpShaders[index];
	}

	return nullptr;
}

// ---------------------------------get----------------------------------
ID3D11RenderTargetView* Renderer::GetRenderTargetView() {
	ID3D11RenderTargetView* pRenderTargetView = nullptr;
	auto hr = _pDevice->CreateRenderTargetView(_pBackBuffer, 0, &pRenderTargetView);
	return pRenderTargetView;
}


ID3D11DepthStencilView* Renderer::GetDepthStencilView() {
	ID3D11DepthStencilView* pDepthStencilView = nullptr;

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = 800;
	depthStencilDesc.Height = 600;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	ID3D11Texture2D*		pDepthStencilBuffer;
	_pDevice->CreateTexture2D(&depthStencilDesc, NULL, &pDepthStencilBuffer);

	_pDevice->CreateDepthStencilView(pDepthStencilBuffer, NULL, &_pDepthStencilView);	//创建深度/模板缓冲区及其相关的深度/模板视口

	return _pDepthStencilView;
}