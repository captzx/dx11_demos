#include "pch.h"
#include "EmptyApp.h"
#include "Window.h"

using namespace insight;

EmptyApp AppInstance;

EmptyApp::EmptyApp() {

}
EmptyApp::~EmptyApp() {

}


bool EmptyApp::ConfigureEngineComponent() {
	return true;
}

void EmptyApp::ShutdownEngineComponent() {

}

void EmptyApp::Initialize() {
	_pWindow = new Window();
	_pWindow->SetCaption(GetName());
	_pWindow->Initialize(this);
}

void EmptyApp::Update() {

}

void EmptyApp::Shutdown() {

}


std::wstring EmptyApp::GetName() {
	return std::wstring(L"EmptyApp Demo");
}