#include "pch.h"
#include "Application.h"
#include "Scene.h"
#include "Timer.h"

using namespace insight;

Application* Application::_pApplication = nullptr;

Application::Application() {
	_pApplication = this;

	_pScene = new Scene();
	_pTimer = new Timer();

}

Application::~Application() {
	SAFE_DELETE(_pScene);
	SAFE_DELETE(_pTimer);
}

Application* Application::GetApplication() {
	return _pApplication;
}