#include "stdafx.h"

using namespace DirectX;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	if (!InitializeWindow(hInstance, nCmdShow, Width, Height, FullScreen))
	{
		MessageBox(0, L"Window Initialization = Failed", L"Error", MB_OK);
		return 0;
	}
	if (!InitD3D())
	{
		MessageBox(Hwnd, L"Failed to initialize directx12", L"Error", MB_OK);
		Cleanup();
		return 1;
	}
	MainLoop();

	// we want to wait for the gpu to finish executing the command list before we start releasing everything
	WaitForPreviousFrame();
	// close the fence event
	CloseHandle(fenceEvent);
	Cleanup();

	return 0;
}