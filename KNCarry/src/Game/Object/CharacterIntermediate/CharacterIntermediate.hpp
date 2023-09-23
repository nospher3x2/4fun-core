#pragma once
#include "../../../Patchables/Offsets.hpp"

class CharacterIntermediate
{
public:
	CLASS_GETTER(float, GetPercentCooldownMod, 0x0)
	CLASS_GETTER(float, GetAbilityHasteMod, 24)
	CLASS_GETTER(float, GetPercentCooldownCapMod, 48)
	CLASS_GETTER(float, GetPassiveCooldownEndTime, 72)
	CLASS_GETTER(float, GetPassiveCooldownTotalTime, 96)
	CLASS_GETTER(float, GetFlatPhysicalDamageMod, 192)
	CLASS_GETTER(float, GetPercentPhysicalDamageMod, 216)
	CLASS_GETTER(float, GetPercentBonusPhysicalDamageMod, 240)
	CLASS_GETTER(float, GetPercentBasePhysicalDamageAsFlatBonusMod, 264)
	CLASS_GETTER(float, GetFlatMagicDamageMod, 288)
	CLASS_GETTER(float, GetPercentMagicDamageMod, 312)
	CLASS_GETTER(float, GetFlatMagicReduction, 336)
	CLASS_GETTER(float, GetPercentMagicReduction, 360)
	CLASS_GETTER(float, GetFlatCastRangeMod, 384)
	CLASS_GETTER(float, GetAttackSpeedMod, 408)
	CLASS_GETTER(float, GetPercentAttackSpeedMod, 432)
	CLASS_GETTER(float, GetPercentMultiplicativeAttackSpeedMod, 456)
	CLASS_GETTER(float, GetBaseAttackDamage, 480)
	CLASS_GETTER(float, GetBaseAttackDamageSansPercentScale, 504)
	CLASS_GETTER(float, GetFlatBaseAttackDamageMod, 528)
	CLASS_GETTER(float, GetPercentBaseAttackDamageMod, 552)
	CLASS_GETTER(float, GetBaseAbilityDamage, 576)
	CLASS_GETTER(float, GetCritDamageMultiplier, 600)
	CLASS_GETTER(float, ScaleSkinCoef, 624)
	CLASS_GETTER(float, GetDodge, 648)
	CLASS_GETTER(float, GetCrit, 672)
	CLASS_GETTER(float, GetArmor, 720)
	CLASS_GETTER(float, GetBonusArmor, 744)
	CLASS_GETTER(float, GetSpellBlock, 768)
	CLASS_GETTER(float, GetBonusSpellBlock, 792)
	CLASS_GETTER(float, GetHPRegenRate, 816)
	CLASS_GETTER(float, GetBaseHPRegenRate, 840)
	CLASS_GETTER(float, GetMoveSpeed, 864)
	CLASS_GETTER(float, GetMoveSpeedBaseIncrease, 888)
	CLASS_GETTER(float, GetAttackRange, 912)
	CLASS_GETTER(float, FlatBubbleRadiusMod, 936)
	CLASS_GETTER(float, PercentBubbleRadiusMod, 960)
	CLASS_GETTER(float, GetFlatArmorPenetration, 984)
	CLASS_GETTER(float, GetPhysicalLethality, 1008)
	CLASS_GETTER(float, GetPercentArmorPenetration, 1032)
	CLASS_GETTER(float, GetPercentBonusArmorPenetration, 1056)
	CLASS_GETTER(float, GetPercentCritBonusArmorPenetration, 1080)
	CLASS_GETTER(float, GetPercentCritTotalArmorPenetration, 1104)
	CLASS_GETTER(float, GetFlatMagicPenetration, 1128)
	CLASS_GETTER(float, GetMagicLethality, 1152)
	CLASS_GETTER(float, GetPercentMagicPenetration, 1176)
	CLASS_GETTER(float, GetPercentBonusMagicPenetration, 1200)
	CLASS_GETTER(float, GetPercentLifeStealMod, 1224)
	CLASS_GETTER(float, GetPercentSpellVampMod, 1248)
	CLASS_GETTER(float, GetPercentPhysicalVamp, 1296)
	CLASS_GETTER(float, GetPathfindingRadiusMod, 1320)
	CLASS_GETTER(float, GetPercentCCReduction, 1344)
	CLASS_GETTER(float, GetPercentEXPBonus, 1368)
	CLASS_GETTER(float, FlatBaseArmorMod, 1392)
	CLASS_GETTER(float, GetPARRegenRate, 1440)
	CLASS_GETTER(float, FlatBaseSpellBlockMod, 1416)
	CLASS_GETTER(float, GetPrimaryARBaseRegenRateRep, 1464)
	CLASS_GETTER(float, GetSecondaryARRegenRateRep, 1488)
	CLASS_GETTER(float, GetSecondaryARBaseRegenRateRep, 1512)
	CLASS_GETTER(float, GetPercentDamageToBarracksMinionMod, 6736)
	CLASS_GETTER(float, GetFlatDamageReductionFromBarracksMinionMod, 6760)
	CLASS_GETTER(float, GetIncreasedMoveSpeedMinionMod, 6784)
	CLASS_GETTER(float, GetFollowTargetNetID, 10016)
	CLASS_GETTER(float, GetFollowerTargetDelay, 10040)
};
