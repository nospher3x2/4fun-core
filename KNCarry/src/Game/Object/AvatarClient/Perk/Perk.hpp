#pragma once
#include "../../../../Patchables/Offsets.hpp"

enum struct PerkId : std::uint16_t {
	SummonAery = 8214,
	ArcaneComet = 8229,
	PhaseRush = 8230,
	NullifyingOrb = 8224,
	ManaflowBand = 8226,
	NimbusCloak = 8275,
	Transcendence = 8210,
	Celerity = 8234,
	AbsoluteFocus = 8233,
	Scorch = 8237,
	Waterwalking = 8232,
	GatheringStorm = 8236,

	GlacialAugment = 8351,
	Kleptomancy = 8359,
	UnsealedSpellbook = 8360,
	HextechFlashtraption = 8306,
	MagicalFootwear = 8304,
	PerfectTiming = 8313,
	FuturesMarket = 8321,
	MinionDematerializer = 8316,
	BiscuitDelivery = 8345,
	CosmicInsight = 8347,
	ApproachVelocity = 8410,
	TimeWarpTonic = 8352,

	PressTheAttack = 8005,
	LethalTempo = 8008,
	FleetFootwork = 8021,
	Conqueror = 8010,
	Overheal = 9101,
	Triumph = 9111,
	PresenceOfMind = 8009,
	LegendAlacrity = 9104,
	LegendTenacity = 9105,
	LegendBloodline = 9103,
	CoupDeGrace = 8014,
	CutDown = 8017,
	LastStand = 8299,

	Electrocute = 8112,
	Predator = 8124,
	DarkHarvest = 8128,
	HailOfBlades = 9923,
	CheapShot = 8126,
	TasteOfBlood = 8139,
	SuddenImpact = 8143,
	ZombieWard = 8136,
	GhostPoro = 8120,
	EyeballCollection = 8138,
	RavenousHunter = 8135,
	IngeniousHunter = 8134,
	RelentlessHunter = 8105,
	UltimateHunter = 8106,

	GraspOfTheUndying = 8437,
	Aftershock = 8439,
	Guardian = 8465,
	Demolish = 8446,
	FontOfLife = 8463,
	BonePlating = 8473,
	Conditioning = 8429,
	SecondWind = 8444,
	Chrysalis = 8472,
	Overgrowth = 8451,
	Revitalize = 8453,
	Unflinching = 8242,
	ShieldBash = 8401
};

class Perk
{
public:
	CLASS_GETTER(PerkId, GetId, 0x8)
	CLASS_GETTER(const char*, GetDisplayName, 0x10)
};

