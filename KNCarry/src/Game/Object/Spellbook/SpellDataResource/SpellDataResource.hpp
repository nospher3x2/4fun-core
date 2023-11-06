#pragma once
#include "../../../../Riot/RiotString.hpp"
#include "../../../../Patchables/Offsets.hpp"

class SpellDataResource
{
public:
	CLASS_GETTER(float, GetMissileSpeed, 0x460)
	CLASS_GETTER(float, GetSpellWidth, 0x540)
};
