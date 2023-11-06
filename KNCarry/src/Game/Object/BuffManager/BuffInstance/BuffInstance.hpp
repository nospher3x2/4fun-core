#pragma once
#include "../../../../Patchables/Offsets.hpp"
#include "../../../../Riot/RiotString.hpp"

enum struct BuffType : std::uint8_t {
	Internal = 0,
	Aura,
	CombatEnchancer,
	CombatDehancer,
	SpellShield,
	Stun,
	Invisibility,
	Silence,
	Taunt,
	Berserk,
	Polymorph,
	Slow,
	Snare,
	Damage,
	Heal,
	Haste,
	SpellImmunity,
	PhysicalImmunity,
	Invulnerability,
	AttackSpeedSlow,
	NearSight,
	Currency,
	Fear,
	Charm,
	Poison,
	Suppression,
	Blind,
	Counter,
	Shred,
	Flee,
	Knockup,
	Knockback,
	Disarm,
	Grounded,
	Drowsy,
	Asleep,
	ObscuredBuff,
	ClickproofToEnemies,
	UnKillable
};

class GameObject;
class BuffManager;

class BuffInstance
{
public:
	CLASS_GETTER(BuffType, GetType, 0x8)
	CLASS_GETTER(float, GetStartTime, 0x18)
	CLASS_GETTER(uint32_t, GetCasterNetworkId, 0x20)
	CLASS_GETTER(float, GetEndTime, 0x1C)
	CLASS_GETTER(uint8_t, GetCount, 0x3C)
	CLASS_GETTER(uint8_t, GetStacks, 0x8C)
	CLASS_GETTER(BuffManager*, GetOwnerBuffManager, 0x40)

	[[nodiscard]] const char* GetName() const;
	[[nodiscard]] uint32_t GetHash() const;
	[[nodiscard]] GameObject* GetOwner() const;
	[[nodiscard]] bool IsActive() const;
private:
	class BuffScriptBase
	{
	public:
		CLASS_GETTER(const char*, GetName, 0x8)
		CLASS_GETTER(uint32_t, GetHash, 0x88)
	};

	CLASS_GETTER(BuffScriptBase*, GetScriptBase, 0x10)
};

