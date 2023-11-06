#pragma once
#include <vector>

#include "../../../Patchables/Offsets.hpp"
#include "BuffInstance/BuffInstance.hpp"

class GameObject;

class BuffManager
{
public:
	CLASS_GETTER(GameObject*, GetOwner, 0x8)
	CLASS_GETTER(uint32_t, GetOwnerHandle, 0x10)
	CLASS_GETTER(uint32_t, GetOwnerNetworkId, 0x14)
	CLASS_GETTER(uintptr_t, GetArrayInstanceBegin, 0x18)
	CLASS_GETTER(uintptr_t, GetArrayInstanceEnd, 0x20)

	[[nodiscard]] std::vector<BuffInstance*> GetBuffs() const;
	[[nodiscard]] BuffInstance* GetBuff(uint32_t hash) const;
	[[nodiscard]] BuffInstance* GetBuff(const std::vector<uint32_t>& hashes) const;
	[[nodiscard]] BuffInstance* GetBuffByType(BuffType type) const;

	void ShowDebugImGuiMenu() const;
};

