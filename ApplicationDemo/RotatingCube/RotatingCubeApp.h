#pragma once
#include "Application.h"

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
	Win32Window* _pWindow;

	int _iSwapChain;
};