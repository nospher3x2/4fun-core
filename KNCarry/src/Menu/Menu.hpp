#pragma once
#include <cstdint>
#include "Component/MenuComponent.hpp"
#include "Component/Checkbox/MenuCheckbox.hpp"

class Menu final : public MenuComponent
{
public:
	Menu(uint32_t id, const char* name, bool isRoot);

	MenuCheckbox* AddCheckbox(uint32_t id, const char* name, bool defaultValue);

	void LoadValue() override;
	void OnWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	void Render() override;
private:
	bool IsTreeVisible = false;
	MenuComponent* Add(MenuComponent* component);
};

