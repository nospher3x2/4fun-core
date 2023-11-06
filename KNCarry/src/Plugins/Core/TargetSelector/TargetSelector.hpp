#pragma once
#include <cstdint>
#include <wtypes.h>

enum struct TargetSelectorMode : uint8_t
{
	Menu = 0,
	Automatic,
	LeastAttacks,
	LeastHealth,
	LowestDistanceToPlayer,
	LowestDistanceToMouse
};

class TargetSelector
{
public:
	static void Initialize();
	static void Destroy();

	static void OnTick();
	static void OnPresentDraw();
	static void OnWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};

