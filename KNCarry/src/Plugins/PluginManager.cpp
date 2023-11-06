#include "PluginManager.hpp"

#include "../Menu/Manager/MenuManager.hpp"
#include "../Game/Game.hpp"
#include "../Riot/RiotHash.hpp"

#include "Core/Orbwalker/Orbwalker.hpp"
#include "Champions/Ashe/Ashe.hpp"

bool PluginManager::Initialize()
{
	if (PluginManager::Initialized)
		return false;

	MenuManager::Initialize();
	Orbwalker::Initialize();
	PluginManager::LoadChampionPlugin();

	Menu* menu = MenuManager::CreateMenu(FNV1A32CI("KNCarry"), "Core");
	menu->AddCheckbox(FNV1A32CI("Orbwalker"), "Orbwalker", true);

	PluginManager::Initialized = true;
	return true;
}

bool PluginManager::LoadChampionPlugin()
{
	const GameObject* player = Game::GetPlayer();
	switch(player->GetCharacterData()->GetSkinHash())
	{
	case SDBM32CI("Ashe"):
		return Ashe::Initialize();
	default:
		return false;
	}
}

