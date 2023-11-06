#include "Game.hpp"
#include "../Patchables/Offsets.hpp"
#include "R3DRenderer/R3DRenderer.hpp"

float Game::GetTime()
{
	return *reinterpret_cast<float*>(DEFINE_RVA(Offsets::GAME_TIME));
}

GameObject* Game::GetPlayer()
{
	static const auto localPlayer{ reinterpret_cast<GameObject**>(DEFINE_RVA(Offsets::LOCAL_PLAYER)) };
	return *localPlayer;
}

ElementalTerrain Game::GetSelectedElementalTerrain()
{
	static const uintptr_t missionInfo{ *reinterpret_cast<uintptr_t*>(DEFINE_RVA(Offsets::MissionInfo::INSTANCE)) };
	static auto elementalTerrain = ElementalTerrain::Unknown;
	if (elementalTerrain == ElementalTerrain::Unknown)
	{
		for (int result = 1; result < 8; ++result)
		{
			if (*reinterpret_cast<uint32_t*>(missionInfo + 0x138) & 1 << result)
			{
				elementalTerrain = static_cast<ElementalTerrain>(result);
				break;
			}
		}
	}

	return elementalTerrain;
}

void Game::SendChat(const char* message, ...)
{
	static const uintptr_t chatInstance{
		*reinterpret_cast<uintptr_t*>(DEFINE_RVA(0x21B3D70))
	};

	static const auto fnSendChat{
			reinterpret_cast<void(__fastcall*)(uintptr_t, int)>(DEFINE_RVA(0x3359B0))
	};

	//va_list va;
	//va_start(va, message);
	//char msg[4000];
	//vsprintf_s(msg, message, va);
	//va_end(va);

	fnSendChat(chatInstance, 2);
}

bool Game::IssueMove(const Vector3& position)
{
	//static const auto fnIssueMove{
	//	reinterpret_cast<bool(__fastcall*)(uintptr_t* hudInputLogic, int screenX, int screenY, bool isAttackMove, bool isMinion, int showClick)>
	//	(DEFINE_RVA(0x88BE70))
	//};
	//
	//static const auto hudInput = *reinterpret_cast<uintptr_t**>(
	//		*reinterpret_cast<uintptr_t*>(DEFINE_RVA(0x21893A0))
	//		+ 0x28
	//);
	//
	//Vector2 cursorPosition{};
	//if (!R3DRenderer::WorldToScreen(position, &cursorPosition))
	//	return false;
	//
	//return fnIssueMove(hudInput, int(cursorPosition.x), int(cursorPosition.y), false, 1, true);
}

void Game::IssueAttack(GameObject* target)
{
	//static const auto fnIssueClick{
	//	reinterpret_cast<bool(__fastcall*)(
	//		uintptr_t * hudInputLogic,
	//		int a,
	//		int b,
	//		bool x,
	//		int screenX, 
	//		int screenY, 
	//		int unknown
	//	)>(DEFINE_RVA(0x8A2160))
	//};
	//
	//static const auto hudInput = *reinterpret_cast<uintptr_t**>(
	//	*reinterpret_cast<uintptr_t*>(DEFINE_RVA(0x21893A0))
	//	+ 0x48
	//);
	//
	//Vector3 targetPosition = target->GetPosition();
	//Vector2 screenPosition{};
	//if (!R3DRenderer::WorldToScreen(targetPosition, &screenPosition))
	//	return;
	//
	//fnIssueClick(hudInput, 0, 0, true, screenPosition.x, screenPosition.y, 0);
	//fnIssueClick(hudInput, 1, 0, true, screenPosition.x, screenPosition.y, 0);

 // #define fIssueClick 0x8A2160 // 44 88 44 24 18 48 89 4C 24 08 55 56 41 54 41 55 41 56 48 8D 6C 24 E1 48 81 EC B0 00 00 00
}

