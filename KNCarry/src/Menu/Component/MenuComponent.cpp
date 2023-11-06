#include "MenuComponent.hpp"
#include "../Menu.hpp"
#include "../../Drawing/ImGui/imgui.h"

MenuComponent::MenuComponent(const uint32_t id, const std::map<uint32_t, MenuComponent*>& children)
{
	this->Id = id;
	this->Children = children;
}

Menu* MenuComponent::GetRoot()
{
	if (this->IsRoot)
		return dynamic_cast<Menu*>(this);

	return this->Parent ? this->Parent->GetRoot() : nullptr;
}

MenuComponent* MenuComponent::SetTooltip(const char* tooltip)
{
	this->Tooltip = tooltip;
	return this;
}

void MenuComponent::Dispose() const
{
	if (this->Parent->Children.contains(this->Id))
	{
		this->Parent->Children.erase(this->Id);
	}
}

void MenuComponent::Render()
{
	if (!this->Tooltip)
		return;

	ImGui::SameLine(0, -1.f);
	::ImGui::TextDisabled("(?)");
	if (::ImGui::IsItemHovered())
	{
		::ImGui::BeginTooltip();
		::ImGui::PushTextWrapPos(::ImGui::GetFontSize() * 35.0f);
		::ImGui::TextUnformatted(this->Tooltip);
		::ImGui::PopTextWrapPos();
		::ImGui::EndTooltip();
	}
}

void MenuComponent::OnWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

}

void MenuComponent::LoadValue()
{
	
}




