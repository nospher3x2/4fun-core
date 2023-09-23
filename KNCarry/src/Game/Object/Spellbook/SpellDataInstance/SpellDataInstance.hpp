#pragma once
#include "../../../../Patchables/Offsets.hpp"

#include "../TargetClient/TargetClient.hpp"
#include "../SpellData/SpellData.hpp"

class GameObject;

class SpellDataInstance
{
public:
	CLASS_GETTER(uint8_t, GetLevel, 0x28)
	CLASS_GETTER(float, GetExpireTime, 0x30)
	CLASS_GETTER(uint8_t, GetAmmo, 0x5C)
	CLASS_GETTER(TargetClient*, GetTargetClient, 0x128)
	CLASS_GETTER(SpellData*, GetSpellData, 0x130)

	bool Cast();
	bool Cast(GameObject* target);
	bool Cast(const Vector3& position);
	bool Cast(const Vector3& startPosition, const Vector3& endPosition);

	void ShowDebugMessage() const;
private:
	static uintptr_t* GetHudSpellLogic();
};
