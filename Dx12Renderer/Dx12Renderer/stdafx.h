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

#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }

struct Vertex
{
	DirectX::XMFLOAT3 position;
};

//Window Setting Variable
static HWND Hwnd = nullptr;
static LPCTSTR WindowName = L"DX12RendererWindow";
static LPCTSTR WindowTitle = L"DX12 Renderer";

static int Width = 800;
static int Height = 600;

static bool FullScreen = false;
static bool Running = true;

//Dx12 Setting Variables
static const int frameBufferCount = 3;

static ID3D12Device* device; // direct3d device

static IDXGISwapChain3* swapChain; // swapchain used to switch between render targets

static ID3D12CommandQueue* commandQueue; // container for command lists

static ID3D12DescriptorHeap* rtvDescriptorHeap; // a descriptor heap to hold resources like the render targets

static ID3D12Resource* renderTargets[frameBufferCount]; // number of render targets equal to buffer count

static ID3D12CommandAllocator* commandAllocator[frameBufferCount]; // we want enough allocators for each buffer * number of threads (we only have one thread)

static ID3D12GraphicsCommandList* commandList; // a command list we can record commands into, then execute them to render the frame

static ID3D12Fence* fence[frameBufferCount];    // an object that is locked while our command list is being executed by the gpu. We need as many 
//as we have allocators (more if we want to know when the gpu is finished with an asset)

static HANDLE fenceEvent; // a handle to an event when our fence is unlocked by the gpu

static UINT64 fenceValue[frameBufferCount]; // this value is incremented each frame. each fence will have its own value

static int frameIndex; // current rtv we are on

static int rtvDescriptorSize; // size of the rtv descriptor on the device (all front and back buffers will be the same size)

//PSO
static ID3D12PipelineState* pipelineStateObject;
static ID3D12RootSignature* rootSignature;
static D3D12_VIEWPORT viewport;
static D3D12_RECT scissorRect;
static ID3D12Resource* vertexBuffer;
static D3D12_VERTEX_BUFFER_VIEW vertexBufferView;

// function declarations
bool InitializeWindow(HINSTANCE hInstance, int ShowWnd, int Width, int Height, bool FullScreen);
void MainLoop();

bool InitD3D(); // initializes direct3d 12

void Update(); // update the game logic

void UpdatePipeline(); // update the direct3d pipeline (update command lists)

void Render(); // execute the command list

void Cleanup(); // release com ojects and clean up memory

void WaitForPreviousFrame(); // wait until gpu is finished with command list


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
