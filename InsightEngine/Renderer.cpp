#include "pch.h"
#include "Renderer.h"
#include "RenderingPipeline.h"
#include "SwapChain.h"
#include "Application.h"
#include "Window.h"

using namespace insight;


Renderer::Renderer():
	_pImmPipeline(new RenderingPipeline())
{

}
Renderer::~Renderer() {
	Shutdown();
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

bool Renderer::CreateSwapChain(const HWND& hwnd) {
	HRESULT hr = S_OK;

	IDXGIDevice* pDXGIDevice = nullptr;
	_pDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void **>(&pDXGIDevice));

	IDXGIAdapter* pDXGIAdapter = nullptr;
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void **>(&pDXGIAdapter));

	IDXGIFactory* pDXGIFactory = nullptr;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void **>(&pDXGIFactory));

	DXGI_SWAP_CHAIN_DESC scDesc;
	scDesc.BufferDesc.Width = 800;
	scDesc.BufferDesc.Height =600;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;

	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.BufferCount = 1;
	scDesc.OutputWindow = hwnd;
	scDesc.Windowed = true;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scDesc.Flags = 0;

	hr = pDXGIFactory->CreateSwapChain(_pDevice, &scDesc, &_pSwapChain);
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

void Renderer::Present() {
	_pSwapChain->Present(0, 0);
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

	_pDevice->CreateDepthStencilView(pDepthStencilBuffer, NULL, &_pDepthStencilView);	//�������/ģ�建����������ص����/ģ���ӿ�

	return _pDepthStencilView;
}