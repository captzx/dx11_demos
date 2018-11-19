#pragma once
#include "Application.h"
#include "ResourceProxy.h"

class RotatingCubeApp: public Application {
public:
	RotatingCubeApp();

public:
	virtual bool ConfigureEngineComponent();
	virtual void ShutdownEngineComponent();

	virtual void Initialize();
	virtual void Update();
	virtual void Shutdown();

	virtual std::wstring GetName();

protected:
	Renderer* _pRenderer;
	Win32Window* _pWindow;

	int _iSwapChain;
	std::shared_ptr<ResourceProxy> _pRenderTarget;
	std::shared_ptr<ResourceProxy> _pDepthTarget;

	std::shared_ptr<ResourceProxy> _pVertexBuffer;
	int _iVertexLayout;
	std::shared_ptr<ResourceProxy> _pIndexBuffer;
	RenderEffect* _pEffect;

	XMFLOAT4X4 _mWorld;
	XMFLOAT4X4 _mView;
	XMFLOAT4X4 _mProj;

	IParameterManager* _pParamMgr;
};