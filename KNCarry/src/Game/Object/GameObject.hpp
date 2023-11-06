#pragma once
#include "../../Patchables/Offsets.hpp"
#include "../../Riot/RiotString.hpp"
#include "../../Math/Vector.hpp"

#include "./CharacterData/CharacterData.hpp"
#include "./Experience/Experience.hpp"
#include "./Spellbook/SpellbookClient.hpp"
#include "./CharacterIntermediate/CharacterIntermediate.hpp"
#include "./BuffManager/BuffManager.hpp"
#include "./HeroInventoryCommon/HeroInventoryCommon.hpp"
#include "./AvatarClient/AvatarClient.hpp"
#include "./PathControllerCommon/PathControllerCommon.hpp"
#include "UnitInfoComponent/UnitInfoComponent.hpp"

enum struct StatusFlag : uint16_t {
	Invulnerable = 1 << 0,
	WillRevive = 1 << 1,
	Unstoppable = 1 << 2,
	WontDieLowHealth = 1 << 4,
	MagicImmune = 1 << 6,
	PhysicalImmune = 1 << 7,
	SpellImmune = 1 << 8,
	Channeling = 1 << 10
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

enum struct ObjectTypeFlag : uint32_t {
	GameObject = (1 << 0),  //0x1
	NeutralCamp = (1 << 1),  //0x2
	DeadObject = (1 << 4),  //0x10
	InvalidObject = (1 << 5),  //0x20
	AIBaseCommon = (1 << 7),  //0x80
	AttackableUnit = (1 << 9),  //0x200
	AI = (1 << 10), //0x400
	AIMinionClient = (1 << 11), //0x800
	AIHeroClient = (1 << 12), //0x1000
	AITurretClient = (1 << 13), //0x2000
	Unknown0 = (1 << 14), //0x4000
	MissileClient = (1 << 15), //0x8000
	AIMarker = (1 << 16), //0x10000
	AnimatedBuilding = (1 << 17), //0x20000
	Unknown2 = (1 << 18), //0x40000
	Unknown3 = (1 << 19), //0x80000	

	EffectEmitter = AttackableUnit | DeadObject | NeutralCamp
};

enum struct CombatType : uint8_t {
	Melee = 1,
	Ranged = 2
};

class GameObject
{
public:
	CLASS_GETTER(uintptr_t*, GetVTable, 0x0)
	CLASS_GETTER(uint32_t, GetHandle, 0x10)
	CLASS_GETTER(uint8_t, GetTeam, 0x3C)
	CLASS_GETTER(std::string, GetName, 0x60)
	CLASS_GETTER(uint32_t, GetNetworkId, 0xC8)
	CLASS_GETTER(Vector3, GetPosition, 0x220)
	CLASS_GETTER(SpellCastInfo*, GetSpellCastInfo, 0x2E8)
	CLASS_GETTER(bool, IsVisible, 0x310)
	CLASS_GETTER(float, GetPAR, 0x350)
	CLASS_GETTER(float, GetMaxPAR, 0x368)
	CLASS_GETTER(bool, IsPAREnabled, 0x380)
	CLASS_GETTER(float, GetSAR, 0x3F8)
	CLASS_GETTER(float, GetMaxSAR, 0x410)
	CLASS_GETTER(bool, IsSAREnabled, 0x428)
	CLASS_GETTER(StatusFlag, GetStatusFlag, 0x500)
	CLASS_GETTER(float, GetLifetime, 0xDF0)
	CLASS_GETTER(float, GetMaxLifetime, 0xE18)
	CLASS_GETTER(float, GetLifetimeTicks, 0xE20)
	CLASS_GETTER(bool, IsTargetable, 0xEC0)
	CLASS_GETTER(uint32_t, IsTargetableToTeamFlags, 0xED8)
	CLASS_GETTER(uint8_t, GetRecallState, 0xF50)
	CLASS_GETTER(float, GetHealth, 0x1068)
	CLASS_GETTER(float, GetMaxHealth, 0x1080)
	CLASS_GETTER(float, GetAllShield, 0x10C8)
	CLASS_GETTER(float, GetPhysicalShield, 0x10E0)
	CLASS_GETTER(float, GetMagicalShield, 0x10F8)
	CLASS_GETTER(float, GetChampSpecificHealth, 0x1110)
	CLASS_GETTER(float, GetIncomingHealingAllied, 0x1128)
	CLASS_GETTER(float, GetIncomingHealingEnemy, 0x1140)
	CLASS_GETTER(float, GetIncomingDamage, 0x1158)
	CLASS_GETTER(float, GetStopShieldFade, 0x1170)
	CLASS_GETTER(ActionState, GetActionState, 0x13D0)
	CLASS_GETTER(ActionState, GetActionState2, 0x13E8)
	CLASS_GETTER(float, GetGoldTotal, 0x2170)
	CLASS_GETTER(float, GetMinimumGold, 0x2188)
	CLASS_GETTER(Vector3, GetDirection, 0x2210)
	CLASS_GETTER(CombatType, GetCombatType, 0x2670)
	CLASS_GETTER(UnitInfoComponent*, GetUnitInfoComponent, 0x3530)
	CLASS_GETTER(CharacterData*, GetCharacterData, 0x35A0)
	CLASS_GETTER(float, GetNumNeutralMinionsKilled, 18656)
	CLASS_GETTER(float, GetVisionScore, 0x4018)
	CLASS_GETTER(AvatarClient*, GetAvatarClient, 0x4620)
	CLASS_GETTER(float, GetShutdownValue, 0x48C0)
	CLASS_GETTER(float, GetBaseGoldGivenOnDeath, 0x48D8)

	[[nodiscard]] CharacterIntermediate* GetCharacterIntermediate() const;
	[[nodiscard]] BuffManager* GetBuffManager() const;
	[[nodiscard]] SpellbookClient* GetSpellbook() const;
	[[nodiscard]] Experience* GetExperience() const;
	[[nodiscard]] HeroInventoryCommon* GetHeroInventoryCommon() const;
	[[nodiscard]] PathControllerCommon* GetPathControllerCommon();
	[[nodiscard]] GameObject* GetGoldRedirectTarget();

	[[nodiscard]] bool IsZombie() const;
	[[nodiscard]] uint32_t GetTypeFlags() const;
	[[nodiscard]] bool IsOnScreen() const;
	[[nodiscard]] bool IsDead() const;
	[[nodiscard]] bool CompareObjectTypeFlag(ObjectTypeFlag flag) const;

	[[nodiscard]] void* GetCircleIconPortrait() const;
	[[nodiscard]] void* GetSquareIconPortrait() const;

	[[nodiscard]] float GetAttackDelay() const;
	[[nodiscard]] float GetAttackCastDelay() const;

	[[nodiscard]] float GetBoundingRadius();
	[[nodiscard]] float GetDeathDuration();
	[[nodiscard]] float GetRespawnTimeRemaining();

	[[nodiscard]] bool IsRecalling() const;
	[[nodiscard]] bool IsMe() const;
	[[nodiscard]] bool IsAlly(const GameObject* other = nullptr) const;
	[[nodiscard]] bool IsEnemy(const GameObject* other = nullptr) const;

	[[nodiscard]] bool IsAI() const;
	[[nodiscard]] bool IsMinion() const;
	[[nodiscard]] bool IsHero() const;
	[[nodiscard]] bool IsTurret() const;
	[[nodiscard]] bool IsMissile() const;
	[[nodiscard]] bool IsBuilding() const;
	[[nodiscard]] bool IsAttackableUnit() const;
	[[nodiscard]] bool IsEffectEmitter() const;

	[[nodiscard]] bool IsMelee() const;
	[[nodiscard]] bool IsRanged() const;

	[[nodiscard]] bool CanCast() const;
	[[nodiscard]] bool CanMove() const;
	[[nodiscard]] bool CanAttack() const;

	[[nodiscard]] bool IsAttackable(bool ignoreAlly = true) const;
	[[nodiscard]] bool IsUnderTurret(bool includeAllyTurret = false);

	[[nodiscard]] float GetDistanceSqrt(const GameObject* object) const;
	[[nodiscard]] float GetDistanceSqrt(const Vector3& position) const;
	[[nodiscard]] float GetDistance(const GameObject* object) const;
	[[nodiscard]] float GetDistance(const Vector3& position) const;
	[[nodiscard]] float GetRealAttackRange();

	void ShowDebugImGuiMenu();
};

