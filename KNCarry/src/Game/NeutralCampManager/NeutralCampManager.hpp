#pragma once
#include "../../Patchables/Offsets.hpp"

enum struct CampId : uint8_t {
	BlueOrder = 1,
	WolvesOrder,
	RaptorsOrder,
	RedOrder,
	KrugsOrder,
	Dragon,
	BlueChaos,
	WolvesChaos,
	RaptorsChaos,
	RedChaos,
	KrugsChaos,
	Baron,
	GrompOrder,
	GrompChaos,
	CrabBottom,
	CrabTop,
	Herald
};

class GameObject;	

class NeutralCampManager
{
public:
	static GameObject* GetCampObject(CampId campId);
	static float GetTimerExpiry(GameObject* camp);
private:
	static uintptr_t* GetInstance();
};

