#include "ManagerTemplate.hpp"
#include "../../Patchables/Offsets.hpp"

RiotArray<GameObject*>& ManagerTemplate::GetHeroes()
{
	return ManagerTemplate::GetRiotArray(Offsets::ManagerTemplate::HERO_MANAGER);
}

RiotArray<GameObject*>& ManagerTemplate::GetMinions()
{
	return ManagerTemplate::GetRiotArray(Offsets::ManagerTemplate::MINION_MANAGER);
}

RiotArray<GameObject*>& ManagerTemplate::GetTurrets()
{
	return ManagerTemplate::GetRiotArray(Offsets::ManagerTemplate::TURRET_MANAGER);
}

std::map<uint32_t, GameObject*> ManagerTemplate::GetMissiles() {
	uintptr_t* missileManager = *reinterpret_cast<uintptr_t**>(DEFINE_RVA(Offsets::ManagerTemplate::MISSILE_MANAGER));
	return *reinterpret_cast<std::map<uint32_t, GameObject*>*>(missileManager + 0x8);
}

RiotArray<GameObject*>& ManagerTemplate::GetRiotArray(const uintptr_t& offset)
{
	return **reinterpret_cast<RiotArray<GameObject*>**>(DEFINE_RVA(offset));
}
