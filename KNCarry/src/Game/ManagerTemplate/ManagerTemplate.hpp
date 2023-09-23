#pragma once
#include "../Object/GameObject.hpp"
#include "../../Riot/RiotArray.hpp"
#include <map>

class ManagerTemplate
{
public:
	static RiotArray<GameObject*>& GetHeroes();
	static RiotArray<GameObject*>& GetMinions();
	static RiotArray<GameObject*>& GetTurrets();
	static RiotArray<GameObject*>& GetInhibitors();

	static std::map<uint32_t, GameObject*> GetMissiles();
private:
	struct MissileManager
	{
		uintptr_t* VTable; // 0x0
		std::map<uint32_t, GameObject*> MissileMap; // 0x8
	};

	static RiotArray<GameObject*>& GetRiotArray(const uintptr_t& offset);
};

