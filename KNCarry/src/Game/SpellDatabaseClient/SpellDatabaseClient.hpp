#pragma once
#include "../../Patchables/Offsets.hpp"

class SpellData;

class SpellDatabaseClient
{
public:
	static bool HasData(uint32_t hash);
	static SpellData* GetData(uint32_t hash);
private:
	static uintptr_t* GetInstance();
};

