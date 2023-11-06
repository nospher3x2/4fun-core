#include "MenuManager.hpp"

#include "../../Drawing/ImGui/imgui.h"
#include "../../Riot/RiotHash.hpp"
#include "../../EventHandler/EventHandler.hpp"

void MenuManager::Initialize()
{
	MenuManager::Root = new Menu(FNV1A32CI("Root"), "", true);
	MenuManager::Root->IsMenu = false;
	MenuManager::Root->IsVisible = false;

	EventHandler::Add(EventType::OnPresentDraw, OnPresentDraw);
	EventHandler::Add(EventType::OnWndProc, OnWndProc);
}

Menu* MenuManager::GetMenu(const uint32_t id)
{
	if (MenuManager::Root->Children.contains(id))
		return dynamic_cast<Menu*>(MenuManager::Root->Children[id]);

	return nullptr;
}

Menu* MenuManager::CreateMenu(uint32_t id, const char* name)
{
	if (MenuManager::Root->Children.contains(id))
		return nullptr;

	const auto menu = new Menu{ id, name, true };
	menu->LoadValue();

	menu->Parent = MenuManager::Root;
	MenuManager::Root->Children.emplace(id, menu);
	return menu;
}

void MenuManager::OnPresentDraw()
{
	if (!MenuManager::Root->IsVisible)
		return;

	ImGui::SetNextWindowPos({ 25.f, 25.f }, ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize({ 800.f, 600.f }, ImGuiCond_FirstUseEver);
	ImGui::Begin("Menu", &MenuManager::Root->IsVisible, ImGuiWindowFlags_NoCollapse);
	{
		for (const auto& [id, component] : MenuManager::Root->Children)
		{
			component->Render();
		}
	}
	ImGui::End();
}

void MenuManager::OnWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case VK_SHIFT:
			MenuManager::Root->IsVisible = !MenuManager::Root->IsVisible;
			break;
		case VK_F9:
			//Save
			break;
		default:
			break;
		}
	}

	for (const auto& [id, component] : MenuManager::Root->Children)
	{
		if (!component->IsMenu)
			continue;

		component->OnWndProc(hWnd, uMsg, wParam, lParam);
	}
}

