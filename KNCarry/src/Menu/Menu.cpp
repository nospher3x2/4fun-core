#include "Menu.hpp"
#include "../Logger/Logger.hpp"

Menu::Menu(const uint32_t id, const char* name, const bool isRoot) : MenuComponent(id, {})
{
	this->IsRoot = isRoot;
	this->IsMenu = true;
	this->DisplayName = name;
}

MenuComponent* Menu::Add(MenuComponent* component)
{
	if (component == nullptr)
		return this;

	if (component->IsRoot)
	{
		Logger::Error("Cannot add root component to menu");
		return this;
	}

	if (this->Children.contains(component->Id))
	{
		Logger::Error("The menu %s already contains a child with id %d", this->DisplayName, component->Id);
		return this;
	}

	component->Parent = this;
	this->Children.emplace(component->Id, component);

	if (this->GetRoot() != nullptr)
	{
		component->LoadValue();
	}

	return this;
}

MenuCheckbox* Menu::AddCheckbox(const uint32_t id, const char* name, const bool defaultValue)
{
	return dynamic_cast<MenuCheckbox*>(
		this->Add(
			new MenuCheckbox(id, name, defaultValue)
		)
	);
}

void Menu::LoadValue()
{
	for (const auto& [id, component] : this->Children)
	{
		component->LoadValue();
	}
}

void Menu::OnWndProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
{
	for (const auto& [id, component] : this->Children)
	{
		component->OnWndProc(hWnd, uMsg, wParam, lParam);
	}
}

void Menu::Render()
{
	if (!this->IsVisible)
		return;

	if (this->IsRoot)
	{
		ImGui::SetNextItemOpen(this->IsTreeVisible, ImGuiCond_Once);
		if (ImGui::CollapsingHeader(this->DisplayName, ImGuiTreeNodeFlags_DefaultOpen))
		{
			for (const auto& [id, component] : this->Children)
			{
				component->Render();
			}

			if (!this->IsTreeVisible)
			{
				// callback on value changed.
			}

			this->IsTreeVisible = true;
		} else if (this->IsTreeVisible)
		{
			// callback on value changed.
			this->IsTreeVisible = false;
		}

		return;
	}

	ImGui::SetNextItemOpen(this->IsTreeVisible, ImGuiCond_Once);
	if (ImGui::TreeNode(this->DisplayName))
	{
		for (const auto& [id, component] : this->Children)
		{
			component->Render();
		}
		ImGui::TreePop();

		if (!this->IsTreeVisible)
		{
			// callback on value changed.
		}

		this->IsTreeVisible = true;
	} else if (this->IsTreeVisible)
	{
		// callback on value changed.
		this->IsTreeVisible = false;
	}
}