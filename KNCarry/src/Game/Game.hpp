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
	static GameObject* GetPlayer();
	static ElementalTerrain GetSelectedElementalTerrain();

	static bool IssueMove(const Vector3& position);
	static void IssueAttack(GameObject* target);
};

