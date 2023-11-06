#pragma once
#include <vector>

class HookManager
{
public:
	static bool Initialize();
	static void InstallHooks();

	static uint8_t GetSpoofedBytes(uintptr_t address);
	static void SaveOriginalByte(uintptr_t address, size_t size);
private:
	typedef char(__fastcall* OnSendChat)(uintptr_t chatInstance, const char* message, int a3);
	struct BytePair
	{
		uintptr_t Address;
		uint8_t OriginalByte;
	};

	static inline std::vector<BytePair> SpoofedBytes{};

	static bool SpoofVirtualProtect();
	static bool SpoofVirtualQuery();
	static bool SpoofStubCrcRoutine();
	static void* InstallTrampoline(uintptr_t address, void* destination, size_t size);

	static uintptr_t GetShadowModule();
	static bool WriteJmp(void* address, void* destination, size_t size);
	//__declspec(naked) static void HookStubCheck();
	//
	//__declspec(naked) static void HookLeagueFirstCheck();
	//
	//__declspec(naked) static void HookLeagueSecondCheck();
	//
	//__declspec(naked) static void HookLeagueThirdCheck();
	//
	//__declspec(naked) static void HookLeagueFourthCheck();

	static inline OnSendChat OriginalSendChat{ nullptr };
	static char HookSendChat(uintptr_t chatInstance, const char* message, int a3);
};

