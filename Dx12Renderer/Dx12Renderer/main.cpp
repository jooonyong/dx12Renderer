#include "stdafx.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	if (!InitializeWindow(hInstance, nCmdShow, Width, Height, FullScreen))
	{
		MessageBox(0, L"Window Initialization = Failed", L"Error", MB_OK);
		return 0;
	}
	MainLoop();
	return 0;
}