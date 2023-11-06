#pragma once
#include <cstdint>
#include <map>
#include <wtypes.h>

class Menu;
class MenuComponent
{
public:
	uint32_t Id = 0;
	const char* DisplayName = nullptr;
	Menu* Parent = nullptr;
	std::map<uint32_t, MenuComponent*> Children;

	bool IsRoot = false;
	bool IsMenu = false;
	bool IsVisible = true;
	bool IsEnabled = false;
	const char* Tooltip = nullptr;

	MenuComponent() = default;
	explicit MenuComponent(uint32_t id, const std::map<uint32_t, MenuComponent*>& children);
	virtual ~MenuComponent() = default;

	Menu* GetRoot();
	MenuComponent* SetTooltip(const char* tooltip);
	void Dispose() const;

	virtual void Render();
	virtual void OnWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void LoadValue();

	template<typename T, std::enable_if_t<std::is_base_of_v<MenuComponent, T>>* = nullptr>
	T As()
	{
		return static_cast<T>(this);
	}
};
