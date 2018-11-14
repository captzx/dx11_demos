#include "pch.h"
#include "RotatingCubeApp.h"
#include "Application.h"
#include "Win32Window.h"
#include "Renderer.h"

#include <glog/logging.h>

using namespace insight;

RotatingCubeApp _RotatingCubeInstance;

RotatingCubeApp::RotatingCubeApp() {
	//LOG(INFO) << "info test" << "hello log!";  //输出一个Info日志
	//LOG(WARNING) << "warning test";  //输出一个Warning日志
	//LOG(ERROR) << "error test";  //输出一个Error日志
}

bool RotatingCubeApp::ConfigureEngineComponent() {
	_pWindow = new Win32Window();
	_pWindow->SetCaption(GetName());
	_pWindow->Initialize(this);

	_pRenderer = new Renderer();
	if (!_pRenderer->Initialize(D3D_DRIVER_TYPE_HARDWARE, D3D_FEATURE_LEVEL_10_0)) {

	}
}

void RotatingCubeApp::ShutdownEngineComponent() {

}

void RotatingCubeApp::Initialize() {

}

void RotatingCubeApp::Update() {

}

void RotatingCubeApp::Shutdown() {

}

std::wstring RotatingCubeApp::GetName() {
	return std::wstring(L"Rotating Cube Application");
}