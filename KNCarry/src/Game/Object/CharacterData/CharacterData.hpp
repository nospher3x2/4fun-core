#pragma once
#include "../../../Riot/RiotString.hpp"
#include "../../../Patchables/Offsets.hpp"

class CharacterData
{
public:
	CLASS_GETTER(RiotString*, GetSkinName, 0x8)
	CLASS_GETTER(uint32_t, GetSkinHash, 0x18)
};
