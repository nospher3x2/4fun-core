#include "MenuCheckbox.hpp"
#include "../../../Drawing/ImGui/imgui.h"

MenuCheckbox::MenuCheckbox(const uint32_t id, const char* name, const bool defaultValue)
	: MenuComponent(id, {})
{
	this->DisplayName = name;
	this->IsEnabled = defaultValue;
}

void MenuCheckbox::LoadValue()
{
	
}

void MenuCheckbox::Render()
{
	if (!this->IsVisible)
		return;

	if (ImGui::Checkbox(this->DisplayName, &this->IsEnabled))
	{
		// callback on value changed.
	}

	MenuComponent::Render();
}

