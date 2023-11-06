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
	static RiotArray<GameObject*>& GetRiotArray(const uintptr_t& offset);
};

