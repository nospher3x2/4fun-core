#pragma once
#include "../../../../Patchables/Offsets.hpp"
#include "../SpellCastInfo/SpellCastInfo.hpp"

class SpellCasterClient
{
public:
	CLASS_GETTER(SpellCastInfo*, GetSpellCastInfo, 0x8)
	CLASS_GETTER(uint8_t, GetSlot, 0x10)
	CLASS_GETTER(float, GetCastTime, 0xF8)
	CLASS_GETTER(float, GetStartTime, 0x188)
	CLASS_GETTER(float, GetEndTime, 0x170C)
};
