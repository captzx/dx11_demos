#pragma once

#include "Application.h"
#include "RenderWindow.h"
#include "Renderer.h"


using namespace insight;

class RotatingCubeApp :public Application {
public:
	RotatingCubeApp();

public:
	virtual bool ConfigureEngineComponent();
	virtual void ShutdownEngineComponent();

	virtual void Initialize();
	virtual void Update();
	virtual void Shutdown();

protected:
	Renderer* _pRenderer;
	RenderWindow* _pWindow;

	int _swapChain;
	std::shared_ptr<Resource> _pRenderTarget;
	std::shared_ptr<Resource> _pDepthTarget;

	std::shared_ptr<Resource> _pVertexBuffer;
	int _vertexLayout;
	std::shared_ptr<Resource> _pIndexBuffer;
	RenderEffect* _pEffect;

	Matrix4f _worldMatrix;
	Matrix4f _viewMatrix;
	Matrix4f _projMatrix;
};