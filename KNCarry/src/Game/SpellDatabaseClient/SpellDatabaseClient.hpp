#pragma once
#include "../../Patchables/Offsets.hpp"

class SpellData;

class SpellDatabaseClient
{
public:
	static SpellData* GetData(uint32_t hash);
private:
	static uintptr_t* GetInstance();
};

