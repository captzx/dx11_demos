#include "pch.h"
#include "RenderWindow.h"
#include "IMsgProc.h"

using namespace xin;

int WINAPI WinMain(HINSTANCE h_Inst, HINSTANCE h_PrevInst, LPSTR lpcmdline, int ncmdshow){
	WindowProcessor winproc;
	RenderWindow window;
	window.Initialize(&winproc);

	MSG msg;

	while (true){
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if (msg.message == WM_QUIT){
				return true;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Call the overloaded application update function.
		//Update();
		//TakeScreenShot();
	}
	return true;
}