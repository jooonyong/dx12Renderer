#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers.
#endif

#include <windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"

static HWND Hwnd = nullptr;
static LPCTSTR WindowName = L"DX12RendererWindow";
static LPCTSTR WindowTitle = L"DX12 Renderer";

static int Width = 800;
static int Height = 600;

static bool FullScreen = false;

bool InitializeWindow(HINSTANCE hInstance, int ShowWnd, int Width, int Height, bool FullScreen);
void MainLoop();


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
