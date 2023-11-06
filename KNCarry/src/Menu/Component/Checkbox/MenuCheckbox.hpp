#pragma once
#include "../MenuComponent.hpp"

class MenuCheckbox final : public MenuComponent
{
public:
	MenuCheckbox(uint32_t id, const char* name, bool defaultValue);

	void LoadValue() override;
	void Render() override;

};

