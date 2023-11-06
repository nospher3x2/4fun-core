#include "Orbwalker.hpp"

#include "../../../Logger/Logger.hpp"
#include "../../../Game/Game.hpp"
#include "../../../Game/R3DRenderer/R3DRenderer.hpp"
#include "../../../Game/ManagerTemplate/ManagerTemplate.hpp"
#include "../../../Game/NeutralCampManager/NeutralCampManager.hpp"
#include "../../../EventHandler/EventHandler.hpp"

void Orbwalker::Initialize()
{
	Logger::Warn("Orbwalker initialized!");

	//EventHandler::Add(EventType::OnTick, OnTick);
	EventHandler::Add(EventType::OnPresentDraw, OnPresentDraw);
}

void Orbwalker::Destroy()
{
	Logger::Warn("Orbwalker destroyed!");

	//EventHandler::Add(EventType::OnTick, OnTick);
	EventHandler::Remove(EventType::OnPresentDraw, OnPresentDraw);
}

void Orbwalker::OnTick()
{
	static uint64_t lastTick = 0;
	static bool x = false;
	GameObject* player = Game::GetPlayer();
	if (GetAsyncKeyState(VK_SPACE) & 1 && GetTickCount64() - lastTick >= 300)
	{

		GameObject* target = nullptr;
		for (GameObject* hero : ManagerTemplate::GetHeroes())
		{
			if (!hero->IsAttackable(true))
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

		Logger::Warn("encontrado target %s", target->GetName().c_str());
		Game::IssueAttack(target);
		lastTick = GetTickCount64();

		SpellbookClient* spellbook = player->GetSpellbook();
	
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
	//if (spellbook->GetSpellState(SpellSlot::Q) != SpellState::Ready)
	//	return;

	//SpellDataInstance* spell = spellbook->GetSpell(SpellSlot::E);
	//if (spell->TargetClient)
	//{
	//	spell->TargetClient->ShowDebugMessage();
	//	
	//}

	SpellCasterClient* activeSpell = spellbook->GetActiveSpell();
	if (activeSpell && !x)
	{
		Logger::Info("Active spell: %i", activeSpell->SpellWasCast());
		Game::SendChat("/pause");
		Game::SendChat("/all oii");

		x = true;

		//if (x == false)
		//{
		//	activeSpell->PrintVTableSpells();
		//	x = true;
		//}
		return;
	}
}

void Orbwalker::OnPresentDraw()
{
	GameObject* player = Game::GetPlayer();
	R3DRenderer::DrawCircle(player->GetPosition(), player->GetRealAttackRange(), ARGB(255, 255, 255, 255), 2.f);

	 PathControllerCommon* pathController = player->GetPathControllerCommon();
	if (pathController && pathController->IsMoving())
	{
		Logger::Info("IsMoving");
		//std::vector<Vector3> waypoints = pathController->GetWaypoints();
		//for (size_t i = 0; i < waypoints.size(); i++)
		//{
		//	R3DRenderer::DrawLine(player->GetPosition(), waypoints[i + 1], ARGB(255, 255, 255, 255), 2.f);
		//	R3DRenderer::DrawCircle(waypoints[i], 50, ARGB(255, 255, 255, 255), 2.f);
		//}
	}

	//uintptr_t x = R3DRenderer::GetTexture("ASSETS/Characters/Ashe/HUD/Ashe_Square.dds");
	//if (x)
	//{
	//	Vector3 playerPosition = player->GetPosition();
	//	Vector2 screenPosition = {};	
	//	R3DRenderer::WorldToScreen(playerPosition, &screenPosition);
	//	//ID3D11ShaderResourceView* resource = *reinterpret_cast<ID3D11ShaderResourceView**>(x + 0x18);
	//	//if (resource)
	//	//{
	//	//	Logger::Warn("not null ptr");
	//	//}
	//
	//	//ImGui::GetWindowDrawList()->AddImage(
	//	//	resource,
	//	//	ImVec2(screenPosition.x - 105, screenPosition.y - 150),
	//	//	ImVec2(screenPosition.x - 105 + 50.f, screenPosition.y - 150 + 50.f),
	//	//	ImVec2(0, 0),
	//	//	ImVec2(1, 1),
	//	//	IM_COL32_WHITE
	//	//);
	//}

	//GameObject* redCamp = NeutralCampManager::GetCampObject(CampId::CrabBottom);
	//if (redCamp)
	//{
	//	//const auto xx = std::to_string(NeutralCampManager::GetTimerExpiry(redCamp));
	//
	//	R3DRenderer::DrawCircle(redCamp->GetPosition(), 100, ARGB(255, 255, 0, 0), 2.f);
	//	//R3DRenderer::DrawTextX(xx.c_str(), 10, redCamp->GetPosition(), ARGB(255, 255, 255, 255), "");
	//}
}