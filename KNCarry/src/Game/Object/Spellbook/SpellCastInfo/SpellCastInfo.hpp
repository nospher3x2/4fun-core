#pragma once
#include "../../../../Patchables/Offsets.hpp"
#include "../../../../Math/Vector.hpp"

#include "../SpellData/SpellData.hpp"

class SpellCastInfo
{
public:
	CLASS_GETTER(SpellData*, GetSpellData, 0x8)
	CLASS_GETTER(const char*, GetSpellName, 0x18)
	CLASS_GETTER(bool, IsAutoAttack, 0x1) // Unknown
	CLASS_GETTER(uint16_t, GetCasterHandle, 0x2) // Unknown
	CLASS_GETTER(uint16_t, GetTargetHandle, 0x3) // Unknown
	CLASS_GETTER(Vector3, GetStartPosition,0x4) // Unknown
	CLASS_GETTER(Vector3, GetEndPosition,  0x5) // Unknown
	CLASS_GETTER(Vector3, GetCastPosition, 0x6) // Unknown
	CLASS_GETTER(float, GetStartTime, 0x7) // Unknown
	CLASS_GETTER(float, GetCastDelay, 0x9) // Unknown
	CLASS_GETTER(float, GetDelay, 0x10) // Unknown
	CLASS_GETTER(uint8_t, GetLevel, 0x11) // Unknown
	CLASS_GETTER(uint8_t, GetSlot, 0x12) // Unknown
};
