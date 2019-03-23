#include "pch.h"
#include "EmptyApp.h"

#include "Window.h"
#include "Renderer.h"
#include "RenderingPipeline.h"
#include "SwapChain.h"

#include "RenderEffect.h"

#include "PipeBufferDesc.h"
#include "PipeTextureDesc.h"
#include "PipeBuffer.h"

#include "Geometry.h"
#include "ParameterManager.h"

using namespace insight;

EmptyApp AppInstance;

bool EmptyApp::ConfigureEngineComponent() {
	int height = 600;
	int width = 800;

	_pWindow = new Window();
	_pWindow->Initialize(this);
	_pWindow->SetWidth(width);
	_pWindow->SetHeight(height);

	_pRenderer = new Renderer();
	_pRenderer->Initialize(D3D_DRIVER_TYPE_HARDWARE, D3D_FEATURE_LEVEL_11_0);

	SwapChainDesc swapChainDesc;
	swapChainDesc.SetOutputWindow(_pWindow->GetHandle());
	swapChainDesc.SetHeight(height);
	swapChainDesc.SetWidth(width);
	_iSwapChain = _pRenderer->CreateSwapChain(swapChainDesc);
	_pWindow->SetSwapChain(_iSwapChain);

	_pRenderTargetView = _pRenderer->GetSwapChainResource(_iSwapChain);

	Texture2dDesc depthStencilDesc;
	depthStencilDesc.SetDepthBuffer(width, height);
	_pDepthStencilView = _pRenderer->CreateTexture2D(&depthStencilDesc, 0);


	_pRenderer->GetPipeline()->OutputMergerStage.ClearDesiredState();
	_pRenderer->GetPipeline()->OutputMergerStage.DesiredState.RenderTargetViews.Set(0, _pRenderTargetView->_iResourceRTV);
	_pRenderer->GetPipeline()->OutputMergerStage.DesiredState.DepthTargetViews.Set(_pDepthStencilView->_iResourceDSV);
	_pRenderer->GetPipeline()->ApplyRenderTargets();


	D3D11_VIEWPORT viewPort;
	viewPort.Width = static_cast<float>(800);
	viewPort.Height = static_cast<float>(600);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;

	int iViewPort = _pRenderer->CreateViewPort(viewPort);
	_pRenderer->GetPipeline()->RasterizerStage.DesiredState.ViewportCount.Set(1);
	_pRenderer->GetPipeline()->RasterizerStage.DesiredState.Viewports.Set(0, iViewPort);

	return true;
}
void EmptyApp::Initialize() {
	_pWindow->SetCaption(GetName());
}

void EmptyApp::Update() {
	_pRenderer->GetPipeline()->ClearColorBuffers(Colors::AliceBlue);
	_pRenderer->GetPipeline()->ClearDepthStencilBuffers();
	
	_pRenderer->Present(_pWindow->GetHandle(), _pWindow->GetSwapChain());
}

void EmptyApp::Shutdown() {

}

void EmptyApp::ShutdownEngineComponent() {
	SAFE_DELETE(_pWindow);
	SAFE_DELETE(_pRenderer);
}

std::wstring EmptyApp::GetName() {
	return std::wstring(L"EmptyApp Demo");
}
