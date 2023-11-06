#include "SpellbookClient.hpp"

SpellDataInstance* SpellbookClient::GetSpell(const uint8_t slot)
{
	return *reinterpret_cast<SpellDataInstance**>(this + Offsets::Spellbook::SPELLS + 0x8 * slot);
}

SpellState SpellbookClient::CanUseSpell(const uint8_t slot)
{
	bool junk{};
	return CallVFunc<SpellState>(this, 2, slot, &junk);
}

float SpellbookClient::GetManaCost(const uint8_t slot)
{
	return *reinterpret_cast<float*>(this + Offsets::Spellbook::GET_MANA + 0x18 * slot);
}