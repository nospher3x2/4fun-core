#include "SpellbookClient.hpp"

SpellDataInstance* SpellbookClient::GetSpell(SpellSlot slot)
{
	return *reinterpret_cast<SpellDataInstance**>(reinterpret_cast<uintptr_t>(this) + 0x6D0 + 0x8 * uint8_t(slot));
}

SpellState SpellbookClient::GetSpellState(SpellSlot slot)
{
	return SpellState::Ready;
}

float SpellbookClient::GetManaCost(SpellSlot slot)
{
	return *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + 0x90 + 0x18 * uint8_t(slot));
}