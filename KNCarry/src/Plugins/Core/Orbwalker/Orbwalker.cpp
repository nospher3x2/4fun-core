#include "Orbwalker.hpp"

#include "../../../Logger/Logger.hpp"
#include "../../../EventHandler/EventHandler.hpp"
#include "../../../Game/Game.hpp"
#include "../../../Game/R3DRenderer/R3DRenderer.hpp"
#include "../../../Game/ManagerTemplate/ManagerTemplate.hpp"
#include "../../../Game/NeutralCampManager/NeutralCampManager.hpp"

void Orbwalker::Initialize()
{
	Logger::Warn("Orbwalker initialized!");

	EventHandler::Add(EventType::OnTick, OnTick);
	EventHandler::Add(EventType::OnPresentDraw, OnPresentDraw);
}

void Orbwalker::Destroy()
{
	Logger::Warn("Orbwalker destroyed!");

	EventHandler::Add(EventType::OnTick, OnTick);
	EventHandler::Remove(EventType::OnPresentDraw, OnPresentDraw);
}

void Orbwalker::OnTick()
{
	static uint64_t lastTick = 0;
	GameObject* player = Game::GetPlayer();
	if (GetAsyncKeyState(VK_SPACE) & 1 && GetTickCount64() - lastTick >= 300)
	{
		GameObject* target = nullptr;
		for (GameObject* hero : ManagerTemplate::GetHeroes())
		{
			if (!hero->IsVisible() || !hero->IsTargetable() || !hero->IsAlive())
				continue;
	
			if (hero->GetTeam() == player->GetTeam())
				continue;

			//if (hero->Position.dist(player->Position) > 600)
			//	continue;

			target = hero;
			break;
		}
	
		if (!target)
		{
			return;
		}

		Logger::Warn("encontrado target %s", target->GetName());
		Game::IssueAttack(target);
		lastTick = GetTickCount64();
	
		//Spellbook* spellbook = player->GetSpellbook();
		//if (!spellbook)
		//{
		//	Logger::Error("Spellbook is null!");
		//	return;
		//}
		//
		//if (spellbook->GetSpellState(SpellSlot::Q) != SpellState::Ready)
		//	return;
		//
		//SpellDataInstance* spell = spellbook->GetSpell(SpellSlot::Q);
		//spell->Cast(target);
		//Logger::Error("Casted Q on %s", target->Name);
	}

	SpellbookClient* spellbook = player->GetSpellbook();
	if (spellbook->GetSpellState(SpellSlot::Q) != SpellState::Ready)
		return;

	//SpellDataInstance* spell = spellbook->GetSpell(SpellSlot::E);
	//if (spell->TargetClient)
	//{
	//	spell->TargetClient->ShowDebugMessage();
	//	
	//}

	//SpellCasterClient* activeSpell = spellbook->ActiveSpell;
	//if (activeSpell)
	//{
	//	Logger::Info("Active spell: %i", activeSpell->Slot);
	//	return;
	//}
}

void Orbwalker::OnPresentDraw()
{
	GameObject* player = Game::GetPlayer();
	R3DRenderer::DrawCircle(player->GetPosition(), player->GetRealAttackRange(), ARGB(255, 255, 255, 255), 2.f);

	Vector3 playerPosition = player->GetPosition();
	void* x = player->GetCircleIconPortrait();
	Vector2 screenPosition = {};
	R3DRenderer::WorldToScreen(playerPosition, &screenPosition);
	ImGui::GetWindowDrawList()->AddImage(
		x,
		ImVec2(100, 100),
		ImVec2(500, 500)
	);

	GameObject* redCamp = NeutralCampManager::GetCampObject(CampId::CrabBottom);
	if (redCamp)
	{
		//const auto xx = std::to_string(NeutralCampManager::GetTimerExpiry(redCamp));

		R3DRenderer::DrawCircle(redCamp->GetPosition(), 100, ARGB(255, 255, 0, 0), 2.f);
		//R3DRenderer::DrawTextX(xx.c_str(), 10, redCamp->GetPosition(), ARGB(255, 255, 255, 255), "");
	}
}