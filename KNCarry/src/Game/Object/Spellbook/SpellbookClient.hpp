#pragma once
#include "../../../Patchables/Offsets.hpp"

#include "./SpellCasterClient/SpellCasterClient.hpp"
#include "./SpellDataInstance/SpellDataInstance.hpp"

enum SpellSlot : uint8_t {
	Q = 0,
	W,
	E,
	R,
	Summoner1,
	Summoner2,
	Item1,
	Item2,
	Item3,
	Item4,
	Item5,
	Item6,
	Trinket,
	Recall,
	EmpoweredAutoAttack = 45,
	EmpoweredAutoAttack1 = 46,
	EmpoweredAutoAttack2 = 47,
	EmpoweredAutoAttack3 = 48,
	EmpoweredAutoAttack4 = 49,
	BasicAttack = 65,
	AlternateBasicAttack = 66
};

enum struct SpellState : int {
	Unknown = -1,
	Ready = 0,
	NotAvailable = 4,
	Supressed = 8,
	NotLearned = 12,
	Channeling = 24,
	Cooldown = 32,
	NoMana = 64,
};

DEFINE_ENUM_FLAG_OPERATORS(SpellState)

class SpellbookClient
{
public:
	CLASS_GETTER(SpellCasterClient*, GetActiveSpell, Offsets::Spellbook::ACTIVE_SPELL)

	SpellDataInstance* GetSpell(uint8_t slot);
	SpellState CanUseSpell(uint8_t slot);
	float GetManaCost(uint8_t slot);
};
