#pragma once
#include <cstdint>
#include "../Menu.hpp"
class MenuManager
{
public:
	static void Initialize();

	static Menu* GetMenu(uint32_t id);
	static Menu* CreateMenu(uint32_t id, const char* name);

	static void OnPresentDraw();
	static void OnWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	static inline Menu* Root = nullptr;
};

