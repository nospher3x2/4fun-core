#pragma once
#include "../../../../Patchables/Offsets.hpp"
#include "../SpellDataResource/SpellDataResource.hpp"

class SpellData
{
public:
	CLASS_GETTER(uint32_t, GetHash, 0x24)
	CLASS_GETTER(std::string, GetName, 0x28)
	CLASS_GETTER(SpellDataResource*, GetSpellDataResource, 0x60)

	void* GetTextureByIndex(uint8_t index)
	{
		return nullptr;
	}
};
