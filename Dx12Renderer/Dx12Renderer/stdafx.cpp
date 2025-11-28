#include "stdafx.h"



bool InitializeWindow(HINSTANCE hInstance, int showWnd, int width, int height, bool fullScreen)
{
    if (FullScreen)
    {
		HMONITOR hMon = MonitorFromWindow(Hwnd, MONITOR_DEFAULTTONEAREST);
		MONITORINFO mi = { sizeof(mi) };
		GetMonitorInfoW(hMon, &mi);

		Width = mi.rcMonitor.right - mi.rcMonitor.left;
		Height = mi.rcMonitor.bottom - mi.rcMonitor.top;
	}

    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WindowName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Error registering class", L"Error", MB_OK | MB_ICONERROR);
        return false;
	}

    Hwnd = CreateWindowEx(NULL, WindowName, WindowTitle, WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,CW_USEDEFAULT,Width,Height,NULL,NULL,hInstance, NULL);
    
    if (!Hwnd)
    {
		MessageBox(NULL, L"Error Creating Window", L"Error", MB_OK | MB_ICONERROR);
        return false;
    }

    if (FullScreen)
    {
        SetWindowLong(Hwnd, GWL_STYLE, 0);
    }

    ShowWindow(Hwnd, showWnd);
	UpdateWindow(Hwnd);
    return true;
}

void MainLoop()
{
    MSG message;
    ZeroMemory(&message, sizeof(MSG));
    
    while (true)
    {
        if(PeekMessage(&message, NULL, 0,0, PM_REMOVE))
        {
            if(message.message == WM_QUIT)
                break;
            
            TranslateMessage(&message);
            DispatchMessage(&message);
		}
        else
        {
            
        }
    }
}

LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
        {
            if(MessageBox(0,L"Are you sure you want to exit?", L"Exit", MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                DestroyWindow(hWnd);
			}
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
		return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
