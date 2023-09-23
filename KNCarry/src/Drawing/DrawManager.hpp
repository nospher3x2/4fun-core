#pragma once
#include <d3d11.h>

struct D3DXRenderer
{
	HWND Window;
	IDXGISwapChain* SwapChain;
	ID3D11RenderTargetView* TargetView ;
	WNDPROC WndProc;
	ID3D11Device* Device;
	ID3D11DeviceContext* Context;
};


class DrawManager
{
public:
	static void Initialize();
	static void Destroy();
private:
	typedef HRESULT(__stdcall* PresentCallback)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

	static HRESULT __stdcall HookPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	static LRESULT __stdcall HookedWindowProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	static inline bool KieroInitialized = false;
	static inline bool ImGuiInitialized = false;
	static inline D3DXRenderer* Renderer = new D3DXRenderer();
	static inline PresentCallback Present = PresentCallback();
	
	static void Draw();

	static void InitRenderer(IDXGISwapChain* swapChain);
	static void StartRenderer();
	static void EndRenderer();

	static void SetContext();
	static void SetImGui();
};

