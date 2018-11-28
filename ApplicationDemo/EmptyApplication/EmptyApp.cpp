#include "pch.h"
#include "EmptyApp.h"
#include "Window.h"

using namespace insight;

EmptyApp AppInstance;

bool EmptyApp::ConfigureEngineComponent() {
	return true;
}

void EmptyApp::ShutdownEngineComponent() {

}

void EmptyApp::Initialize() {
	_pWindow->SetCaption(GetName());
}

void EmptyApp::Update() {

}

void EmptyApp::Shutdown() {

}


std::wstring EmptyApp::GetName() {
	return std::wstring(L"EmptyApp Demo");
}