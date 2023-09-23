#pragma once
#include "../../Patchables/Offsets.hpp"
#include "../../Riot/RiotString.hpp"
#include "../../Math/Vector.h"

#include "./CharacterData/CharacterData.hpp"
#include "./Experience/Experience.hpp"
#include "./Spellbook/SpellbookClient.hpp"
#include "./CharacterIntermediate/CharacterIntermediate.hpp"

enum struct StatusFlag : std::uint16_t {
	Invulnerable = 1 << 0,
	WillRevive = 1 << 1,
	Unstoppable = 1 << 2,
	WontDieLowHealth = 1 << 4,
	MagicImmune = 1 << 6,
	PhysicalImmune = 1 << 7,
	SpellImmune = 1 << 8
};

DEFINE_ENUM_FLAG_OPERATORS(StatusFlag)

enum struct ActionState : uint32_t {
	CanAttack = 1 << 0,
	CanCast = 1 << 1,
	CanMove = 1 << 2,
	Immovable = 1 << 3,
	Unknown = 1 << 4,
	IsStealth = 1 << 5,
	Taunted = 1 << 6,
	Feared = 1 << 7,
	Fleeing = 1 << 8,
	Surpressed = 1 << 9,
	Asleep = 1 << 10,
	NearSight = 1 << 11,
	Ghosted = 1 << 12,
	HasGhost = 1 << 13,
	Charmed = 1 << 14,
	NoRender = 1 << 15,
	ForceRenderParticles = 1 << 16,
	DodgePiercing = 1 << 17,
	DisableAmbientGold = 1 << 18,
	DisableAmbientXP = 1 << 19,
	IsCombatEnchanced = 1 << 20,
	IsSelectable = 1 << 25
};

DEFINE_ENUM_FLAG_OPERATORS(ActionState)

enum struct CombatType : uint8_t {
	Melee = 1,
	Ranged = 2
};

class GameObject
{
public:
	CLASS_GETTER(uintptr_t*, GetVTable, 0x0)
	DEFINE_MEMBER_ENCRYPTED(uintptr_t*, ClassData, 0x8)
	CLASS_GETTER(uint32_t, GetHandle, 0x10)
	CLASS_GETTER(uint8_t, GetTeam, 0x3C)
	CLASS_GETTER(RiotString*, GetNickname, 0x60)
	CLASS_GETTER(uint32_t, GetNetworkId, 0xC8)
	CLASS_GETTER(Vector3, GetPosition, 0x220)
	CLASS_GETTER(bool, IsVisible, 0x310)
	CLASS_GETTER(float, GetPAR, 0x340)
	CLASS_GETTER(float, GetMaxPAR, 0x358)
	CLASS_GETTER(bool, IsPAREnabled, 0x370)
	CLASS_GETTER(float, GetSAR, 0x3E8)
	CLASS_GETTER(float, GetMaxSAR, 0x400)
	CLASS_GETTER(bool, IsSAREnabled, 0x418)
	CLASS_GETTER(StatusFlag, GetStatusFlag, 0x4F0)
	CLASS_GETTER(float, GetLifetime, 0xDE0)
	CLASS_GETTER(float, GetMaxLifetime, 0xDF8)
	CLASS_GETTER(float, GetLifetimeTicks, 0xE10)
	CLASS_GETTER(bool, IsTargetable, 0xEB0)
	CLASS_GETTER(uint32_t, IsTargetableToTeamFlags, 0xEC8)
	CLASS_GETTER(uint8_t, GetRecallState, 0xF40)
	CLASS_GETTER(float, GetHealth, 0x1058)
	CLASS_GETTER(float, GetMaxHealth, 0x1070)
	CLASS_GETTER(float, GetAllShield, 0x10B8)
	CLASS_GETTER(float, GetPhysicalShield, 0x10D0)
	CLASS_GETTER(float, GetMagicalShield, 0x10E8)
	CLASS_GETTER(float, GetChampSpecificHealth, 0x1100)
	CLASS_GETTER(float, GetIncomingHealingAllied, 0x1118)
	CLASS_GETTER(float, GetIncomingHealingEnemy, 0x1130)
	CLASS_GETTER(float, GetIncomingDamage, 0x1148)
	CLASS_GETTER(float, GetStopShieldFade, 0x1160)
	CLASS_GETTER(ActionState, GetState, 0x13C0)
	CLASS_GETTER(ActionState, GetState2, 0x13D8)
	CLASS_GETTER(float, GetGold, 0x2138)
	CLASS_GETTER(float, GetGoldTotal, 0x2150)
	CLASS_GETTER(float, GetMinimumGold, 0x2168)
	CLASS_GETTER(CombatType, GetCombatType, 0x2660)
	CLASS_GETTER(CharacterData*, GetCharacterData, 0x3598)
	CLASS_GETTER(RiotString*, GetName, 0x3860)
	CLASS_GETTER(float, GetNumNeutralMinionsKilled, 0x48F0)
	CLASS_GETTER(float, GetVisionScore, 0x48A8)
	CLASS_GETTER(float, GetShutdownValue, 0x48C0)
	CLASS_GETTER(float, GetBaseGoldGivenOnDeath, 0x48D8)

	CharacterIntermediate* GetCharacterIntermediate();
	SpellbookClient* GetSpellbook();
	Experience* GetExperience();

	float GetRealAttackRange();
	bool IsAlive();
	float GetBoundingRadius();
	GameObject* GetGoldRedirectTarget();
	void* GetCircleIconPortrait();
};

