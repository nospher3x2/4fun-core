#pragma once
#include "../../../../Patchables/Offsets.hpp"
#include "../SpellCastInfo/SpellCastInfo.hpp"
//#include "../../../Logger/Logger.hpp"

class SpellCasterClient
{
public:
	CLASS_GETTER(SpellCastInfo*, GetSpellCastInfo, 0x8)
	CLASS_GETTER(uint8_t, GetSlot, 0x10)
	CLASS_GETTER(uint32_t, GetSourceHandle, 0x90)
	CLASS_GETTER(uint32_t, GetTargetHandle, 0xE8)
	CLASS_GETTER(Vector3, GetStartPosition, 0xAC)
	CLASS_GETTER(Vector3, GetEndPosition, 0xB8)
	CLASS_GETTER(float, GetCastTime, 0xF8)
	CLASS_GETTER(float, GetStartTime, 0x188)
	CLASS_GETTER(float, GetEndTime, 0x170C)

	bool SpellWasCast()
	{
		static const auto fnGetSpellData{
			reinterpret_cast<bool(__fastcall*)(SpellCasterClient*)>(DEFINE_RVA(0x706750))
		};

		return fnGetSpellData(this);
	}

	//void PrintVTableSpells()
	//{
	//	uintptr_t* vtable = *reinterpret_cast<uintptr_t**>(this);
	//	for (int i = 0; i < 20; i++)
	//	{
	//		Logger::Warn("VTable index: %i, address: %s", i, hexify(vtable[i] - Offsets::BASE_ADDRESS).c_str());
	//	}
	//}
};
