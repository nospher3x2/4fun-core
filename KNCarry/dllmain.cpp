#pragma warning(disable : 4996)

#define WIN32_LEAN_AND_MEAN
#include <chrono>
#include <windows.h>
#include "./src/Drawing/DrawManager.hpp"
#include "src/Game/R3DRenderer/R3DRenderer.hpp"
#include "src/Game/ManagerTemplate/ManagerTemplate.hpp"
#include "src/Game/SpellDatabaseClient/SpellDatabaseClient.hpp"
#include "src/Game/Object/GameObject.hpp"
#include <thread>

#include "src/EventHandler/EventHandler.hpp"
#include "src/Game/Game.hpp"
#include "src\Game\Object\Spellbook\SpellbookClient.hpp"
#include "src/Logger/Logger.hpp"
#include "src/Plugins/Core/Orbwalker/Orbwalker.hpp"
#include "src/Utils/Memory/MemoyScanner.hpp"

typedef _Return_type_success_(return >= 0) LONG NTSTATUS;
bool WINAPI HideThread(const HANDLE hThread) noexcept
{
	__try {
		using FnSetInformationThread = NTSTATUS(NTAPI*)(HANDLE threadHandle, UINT threadInformationClass, PVOID threadInformation, ULONG threadInformationLength);
		const auto ntSetInformationThread{
			reinterpret_cast<FnSetInformationThread>(
				::GetProcAddress(::GetModuleHandleW(L"ntdll.dll"), "NtSetInformationThread")
			)
		};

		if (!ntSetInformationThread)
			return false;

		if (const auto status{ ntSetInformationThread(hThread, 0x11u, nullptr, 0ul) }; status == 0x00000000)
			return true;
	}
	__except (TRUE) {
		return false;
	}

	return false;
}

void* spoof_trampoline = 0x0;
__declspec(safebuffers) static void WINAPI DllAttach([[maybe_unused]] LPVOID lp) noexcept
{
	using namespace std::chrono_literals;
	HideThread(::GetCurrentThread());

	Logger::Initialize();
	DrawManager::Initialize();
	R3DRenderer::Initialize();

	Logger::Warn("spoof trampoline: %lu", spoof_trampoline);
	// Plugins
	Orbwalker::Initialize();

	GameObject* player = Game::GetPlayer();

	Experience* experience = player->GetExperience();
	Logger::Warn("Experience: %.2f", experience->GetTotalExperience());
	Logger::Warn("Level: %i", experience->GetLevel());
	Logger::Warn("Spell Training Points: %i", experience->GetSpellTrainingPoints());
	Logger::Error("Get Current Experience: %.2f", experience->GetAmountToNextLevel());
	Logger::Error("Get Exp to Given Level: %.2f", experience->GetExpToGivenLevel(experience->GetLevel() + 1));

	SpellbookClient* spellbook = player->GetSpellbook();
	for (const SpellSlot slot : { SpellSlot::Q, SpellSlot::W, SpellSlot::E })
	{
		SpellDataInstance* spell = spellbook->GetSpell(slot);
		spell->ShowDebugMessage();
		//if (spell->Cast())
		//{
		//	Logger::Info("Casted E");
		//}
	}

	Logger::Warn("Soul: %i", Game::GetSelectedElementalTerrain());
	RiotArray<GameObject*>& heroes = ManagerTemplate::GetHeroes();
	for (GameObject* object : heroes)
	{
		if (!object)
			continue;

		Logger::Info("Bounding Radius: %.2f", object->GetBoundingRadius());
		Logger::Info("Skin Name: %s", object->GetCharacterData()->GetSkinName());
		Logger::Info("Skin Hash: %lu", object->GetCharacterData()->GetSkinHash());

		if (object->GetTeam() != player->GetTeam())
		{	
			spellbook->GetSpell(SpellSlot::W)->Cast(object->GetPosition());
		}
	}

	SpellData* spellData = SpellDatabaseClient::GetData(spellbook->GetSpell(SpellSlot::Q)->GetSpellData()->GetHash());
	if (spellData)
	{
		Logger::Info("Existe data");
		Logger::Info("SpellData encontrado. Name: %s. Hash: %lu", spellData->GetName().c_str(), spellData->GetHash());
	}


	while (true)
	{
		if (GetAsyncKeyState(VK_END) & 1)
			break;

		static UINT64 lastTick = 0;
		if (GetTickCount64() - lastTick >= 30)
		{
			EventHandler::Trigger(EventType::OnTick);
			lastTick = GetTickCount64();
		}
	}

	Orbwalker::Destroy();
	DrawManager::Destroy();
	::ExitProcess(0u);
}

__declspec(safebuffers)BOOL APIENTRY DllMain(const HMODULE hModule, const DWORD reason, [[maybe_unused]] LPVOID reserved)
{
	DisableThreadLibraryCalls(hModule);

	if (reason != DLL_PROCESS_ATTACH)
		return FALSE;

	const uintptr_t baseAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
	if (!GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(baseAddress), &Offsets::MODULE_INFO, sizeof(MODULEINFO)))
		return 0;

	spoof_trampoline = (void*)mem::ScanModInternal((char*)"\xFF\x23", (char*)"xx", (char*)baseAddress);

	HideThread(hModule);
	std::setlocale(LC_ALL, ".utf8");

	_beginthreadex(nullptr, 0u, reinterpret_cast<_beginthreadex_proc_type>(DllAttach), nullptr, 0u, nullptr);
	CloseHandle(hModule);
	return TRUE;
}
