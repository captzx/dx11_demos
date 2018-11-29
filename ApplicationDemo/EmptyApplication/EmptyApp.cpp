#include "pch.h"
#include "EmptyApp.h"
#include "Window.h"

using namespace insight;

Application* AppInstance = new EmptyApp();

void EmptyApp::Initialize() {
	Application::Initialize();
	_pWindow->SetCaption(GetName());
}

std::wstring EmptyApp::GetName() {
	return std::wstring(L"EmptyApp Demo");
}