#include "pch.h"
#include "RotatingCubeApp.h"
#include "Application.h"
#include "Window.h"
#include "renderer.h"

using namespace insight;

RotatingCubeApp RotatingCubeInstance;

void RotatingCubeApp::Initialize() {
	Application::Initialize();
	_pWindow->SetCaption(GetName());
}

bool RotatingCubeApp::ConfigureEngineComponent(){
	return Application::ConfigureEngineComponent();
}
void RotatingCubeApp::ShutdownEngineComponent() {
	Application::ShutdownEngineComponent();
}
void RotatingCubeApp::Update() {
	Application::Update();
}
void RotatingCubeApp::Shutdown() {
	Application::Shutdown();
}


std::wstring RotatingCubeApp::GetName() {
	return std::wstring(L"Rotating Cube Application");
}