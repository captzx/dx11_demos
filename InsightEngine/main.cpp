#include "pch.h"
#include "Application.h"

using namespace insight;

int WINAPI WinMain(HINSTANCE h_Inst, HINSTANCE h_PrevInst, LPSTR lpcmdline, int ncmdshow){
	Application *pApp = Application::Get();

	if (!pApp) {
		// LOG(ERROR) << "There was no instance of the application.";
		return -1;
	}

	if (!pApp->ConfigureEngineComponent()) {
		pApp->ShutdownEngineComponent();
		return 0;
	}

	pApp->Initialize();
	pApp->MessageLoop();
	pApp->Shutdown();
	pApp->ShutdownEngineComponent();
	return 0;
}