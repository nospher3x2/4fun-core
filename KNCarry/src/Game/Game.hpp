#pragma once
#include "../Game/Object/GameObject.hpp"

enum struct ElementalTerrain : uint8_t
{
	Unknown = 0,
	Infernal = 1,
	Mountain = 2,
	Ocean = 3,
	Wind = 4,
	Hextech = 5,
	Chemtech = 6
};

class Game
{
public:
	static float GetTime();
	static GameObject* GetPlayer();
	static ElementalTerrain GetSelectedElementalTerrain();

	static void SendChat(const char* message, ...);
	static bool IssueMove(const Vector3& position);
	static void IssueAttack(GameObject* target);
};

