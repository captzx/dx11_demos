#include "pch.h"
#include "RotatingCubeApp.h"
#include "Application.h"
#include "Window.h"
#include "renderer.h"

using namespace insight;

RotatingCubeApp RotatingCubeInstance;

bool RotatingCubeApp::ConfigureEngineComponent() {
	return true;
}

void RotatingCubeApp::ShutdownEngineComponent() {
	
}

void RotatingCubeApp::Initialize() {
	_pWindow->SetCaption(GetName());
}

void RotatingCubeApp::Update() {
	Application::Update();
}

void RotatingCubeApp::Shutdown() {

}

std::wstring RotatingCubeApp::GetName() {
	return std::wstring(L"Rotating Cube Application");
}