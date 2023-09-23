#pragma once
#include "../../../Patchables/Offsets.hpp"

#include "./SpellCasterClient/SpellCasterClient.hpp"
#include "./SpellDataInstance/SpellDataInstance.hpp"

enum struct SpellSlot : uint8_t {
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

enum struct SpellState : uint8_t
{
	Ready = 1 << 1,
	NotLearned = 1 << 2,
	NotAvaliable = 1 << 3,
	Surpressed = 1 << 4,
	Cooldown = 1 << 5,
	NotEnoughMana = 1 << 6,
	UnknownState = 1 << 7
};

DEFINE_ENUM_FLAG_OPERATORS(SpellState)

class SpellbookClient
{
public:
	CLASS_GETTER(SpellCasterClient*, GetActiveSpell, 0x38)

	SpellDataInstance* GetSpell(SpellSlot slot);
	SpellState GetSpellState(SpellSlot slot);
	float GetManaCost(SpellSlot slot);
};
