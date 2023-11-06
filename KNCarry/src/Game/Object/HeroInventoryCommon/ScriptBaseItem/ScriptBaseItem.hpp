#pragma once
#include "../../../../Patchables/Offsets.hpp"
#include "../ItemData/ItemData.hpp"

class ScriptBaseItem
{
public:
	CLASS_GETTER(ItemData*, GetItemData, 0x38)
	CLASS_GETTER(float, GetPrice, 0x44)
	CLASS_GETTER(float, GetStacks, 0x48)
};