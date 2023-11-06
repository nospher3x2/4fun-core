#include "HookManager.hpp"
#include "../Patchables/Offsets.hpp"
#include "../Logger/Logger.hpp"

#define DEFINE_SHADOW_RVA(address) (HookManager::GetShadowModule() + address)

struct Pair
{
	DWORD64 Key;
	BYTE  Value;
};
inline std::vector<Pair> Pairs {};

//inline std::vector<Pair> Pairs = {};
class C_HookManager
{
public:
	class ByteMap {
	public:

		inline static void Insert(DWORD64 hookAddress, size_t hookSize) {
			for (int i = 0; i <= hookSize; i++) {
				//Pairs.insert({ hookAddress + i, *(BYTE*)(hookAddress + i) });
				Pairs.insert(Pairs.end(), { hookAddress + i, *(BYTE*)(hookAddress + i) });
			}
		}

		inline static DWORD64 FindKey(DWORD64 currentAddress) {
			//if (Pairs.find(currentAddress) != Pairs.end())
			//	return Pairs[currentAddress];

			for (std::size_t i = 0; i <= Pairs.size(); ++i) {
				if (Pairs[i].Key == currentAddress)
					return Pairs[i].Value;
			}
			return *(BYTE*)(currentAddress);
		}

		ByteMap() {}
	};
};

//uintptr_t StubJmpAddress;
//uintptr_t LeagueFirstJmpAddress;
//uintptr_t LeagueSecondJmpAddress;
//uintptr_t LeagueThirdJmpAddress;
//uintptr_t LeagueFourthJmpAddress;
//
//__declspec(naked) void stub_check_hook() {
//	__asm {
//		pushf
//		push rax
//		push rcx
//		push rdx
//		push r8
//
//		mov rcx, rax
//		call C_HookManager::ByteMap::FindKey
//		movzx esi, al
//
//		pop r8
//		pop rdx
//		pop rcx
//		pop rax
//		popf
//		cmp di, si
//		xor esi, r11d
//		and esi, 0x000000FF
//		jmp StubJmpAddress
//	}
//}
//
//__declspec(naked) void league1_check_hook() {
//	__asm {
//		pushf
//		push rax
//		push rcx
//		push rdx
//		push rbx
//		push r8
//
//		add rbx, rcx
//		mov rcx, rbx
//		call C_HookManager::ByteMap::FindKey
//		movzx esi, al
//
//		pop r8
//		pop rbx
//		pop rdx
//		pop rcx
//		pop rax
//		popf
//		cmp r13b, al
//		xor rsi, rax
//		imul rsi, r15
//		jmp LeagueFirstJmpAddress
//	}
//}
//
//__declspec(naked) void league2_check_hook() {
//	__asm {
//		pushf
//		push rcx
//		push rdx
//		push rbx
//		push r8
//
//		add rbx, rax
//		mov rcx, rbx
//		call C_HookManager::ByteMap::FindKey
//		movzx eax, al
//
//		pop r8
//		pop rbx
//		pop rdx
//		pop rcx
//		popf
//		cmovpe rbx, rbx
//		xor rax, rsi
//		shld esi, r14d, 0x10
//		jmp LeagueSecondJmpAddress
//	}
//}
//
//__declspec(naked) void league3_check_hook() {
//	__asm {
//		pushf
//		push rax
//		push rcx
//		push rdx
//		push rsi
//		push r8
//
//		add rsi, rbx
//		mov rcx, rsi
//		call C_HookManager::ByteMap::FindKey
//		movzx ebx, al
//
//		pop r8
//		pop rsi
//		pop rdx
//		pop rcx
//		pop rax
//		popf
//		btc si, r8w
//		inc sil
//		sbb sil, 14
//		jmp LeagueThirdJmpAddress
//	}
//}
//
//__declspec(naked) void league4_check_hook() {
//	__asm {
//		pushf
//		push rcx
//		push rdx
//		push rsi
//		push r8
//
//		add rsi, rax
//		mov rcx, rsi
//		call C_HookManager::ByteMap::FindKey
//		movzx eax, al
//
//		pop r8
//		pop rsi
//		pop rdx
//		pop rcx
//		popf
//		stc
//		test r14d, 0x2665EC7
//		cmp dl, ah
//		jmp LeagueFourthJmpAddress
//	}
//}


bool HookManager::Initialize()
{
	if (!HookManager::SpoofVirtualProtect())
		return false;

	if (!HookManager::SpoofVirtualQuery())
		return false;

	//return HookManager::SpoofStubCrcRoutine();
	return true;
}

void HookManager::InstallHooks()
{
	//HookManager::SaveOriginalByte(DEFINE_RVA(0x4B7670), 17);

	//C_HookManager::ByteMap::Insert(DEFINE_RVA(0x4B7670), 17);
	HookManager::OriginalSendChat = static_cast<OnSendChat>(HookManager::InstallTrampoline(
		0x4B7670,
		reinterpret_cast<void*>(HookManager::HookSendChat),
		17
	));
}

void* HookManager::InstallTrampoline(const uintptr_t address, void* destination, const size_t size)
{
	DWORD64 hookAddress = DEFINE_RVA(address);
	BYTE stub[] = {
		0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
	};
	
	if (size < sizeof(stub)) return NULL;
	
	auto pTrampoline = VirtualAlloc(NULL, size + sizeof(stub), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy(pTrampoline, (PVOID)hookAddress, size); // copy original bytes to trampoline
	
	DWORD64 jmpBack = hookAddress - (DWORD64)pTrampoline - sizeof(stub);
	
	DWORD64 retto = hookAddress + size;
	memcpy(stub + 6, &retto, 8); // write our jmp on byte 6 as the address + length
	memcpy(stub + 6, &jmpBack, 8); // write relative address to jmp opcode
	
	if (DWORD64 shadowModule = HookManager::GetShadowModule())
	{
		HookManager::SaveOriginalByte(hookAddress, size);
		DWORD64 shadowHookAddr = shadowModule + (DWORD64)address;
		uint8_t jmpInstruction[] = {
			0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		};
	
		*((DWORD64*)&jmpInstruction[6]) = reinterpret_cast<uintptr_t>(destination);
		memcpy(reinterpret_cast<void*>(shadowHookAddr), &jmpInstruction, sizeof(jmpInstruction));
	
		for (size_t i = sizeof(jmpInstruction); i < size; i++)
			*reinterpret_cast<std::uint8_t*>(shadowHookAddr + i) = 0x90;
	}
	
	return (void*)reinterpret_cast<DWORD64>(pTrampoline);
}

void HookManager::SaveOriginalByte(const uintptr_t address, const size_t size)
{
	for (int i = 0; i <= size; i++) {
		//Pairs.insert({ hookAddress + i, *(BYTE*)(hookAddress + i) });
		HookManager::SpoofedBytes.insert(
			HookManager::SpoofedBytes.end(), 
			{
				address + i,
				*(BYTE*)(address + i)
			}
		);
	}

	//for (size_t i = 0; i <= size; i++)
	//{
	//	HookManager::OriginalBytes.push_back({
	//		address + i,
	//		*reinterpret_cast<BYTE*>(address + i)
	//	});
	//}
}

uint8_t HookManager::GetSpoofedBytes(uintptr_t address)
{
	for (std::size_t i = 0; i <= HookManager::SpoofedBytes.size(); ++i) {
		if (HookManager::SpoofedBytes[i].Address == address)
			return HookManager::SpoofedBytes[i].OriginalByte;
	}
	return *(BYTE*)(address);
}

bool HookManager::SpoofVirtualProtect()
{
	static constexpr BYTE ZwPvmBytes[] = {
		0x4C, 0x8B, 0xD1, 0xB8, 0x50, 0x00, 0x00, 0x00, 0xF6, 0x04, 0x25, 0x08, 0x03, 0xFE, 0x7F, 0x01
	};

	const HMODULE ntdll = GetModuleHandle(L"ntdll.dll");
	if (!ntdll)
		return false;

	const uintptr_t zwProtectVirtualMemory = reinterpret_cast<uintptr_t>(
		GetProcAddress(ntdll, "ZwProtectVirtualMemory")
	);

	if (!zwProtectVirtualMemory)
		return false;

	for (size_t i = 0; i < sizeof(ZwPvmBytes); i++)
		*reinterpret_cast<BYTE*>(zwProtectVirtualMemory + i) = ZwPvmBytes[i];

	return true;
}

bool HookManager::SpoofVirtualQuery()
{
	static constexpr BYTE ZwQvmBytes[] = {
		0x4C, 0x8B, 0xD1, 0xB8, 0x23, 0x00, 0x00, 0x00, 0xF6, 0x04, 0x25, 0x08, 0x03, 0xFE, 0x7F, 0x01, 0x75, 0x03, 0x0F, 0x05, 0xC3
	};

	const HMODULE ntdll = GetModuleHandle(L"ntdll.dll");
	if (!ntdll)
		return false;

	const uintptr_t zwQueryVirtualMemoryAddr = reinterpret_cast<uintptr_t>(GetProcAddress(ntdll, "ZwQueryVirtualMemory"));

	if (!zwQueryVirtualMemoryAddr)
		return false;

	constexpr auto size = sizeof(ZwQvmBytes);
	DWORD oldPageProtect = 0;
	if (!VirtualProtect(reinterpret_cast<LPVOID>(zwQueryVirtualMemoryAddr), size, PAGE_EXECUTE_READWRITE, &oldPageProtect))
		return false;

	for (size_t i = 0; i < size; i++)
		*reinterpret_cast<BYTE*>(zwQueryVirtualMemoryAddr + i) = ZwQvmBytes[i];

	return VirtualProtect(reinterpret_cast<LPVOID>(zwQueryVirtualMemoryAddr), size, oldPageProtect, nullptr);
}

bool HookManager::SpoofStubCrcRoutine()
{
	const uintptr_t stub_dll = reinterpret_cast<uintptr_t>("stub.dll");
	if (!stub_dll)
		return false;

	//StubJmpAddress = stub_dll + 0x97AEC7 + 15;
	//LeagueFirstJmpAddress = stub_dll + 0xCE70AA + 14;
	//LeagueSecondJmpAddress = stub_dll + 0xCE70C6 + 16;
	//LeagueThirdJmpAddress = stub_dll + 0xCE70EF + 16;
	//LeagueFourthJmpAddress = stub_dll + 0xCE7121 + 14;
	//
	///* Write jmp at stub_check */
	//if (!WriteJmp(reinterpret_cast<void*>(stub_dll + 0x97AEC7), reinterpret_cast<void*>(stub_check_hook), 15))
	//	return false;
	//
	///* Write jmp at first league_check */
	//if (!WriteJmp(reinterpret_cast<void*>(stub_dll + 0xCE70AA), reinterpret_cast<void*>(league1_check_hook), 14))
	//	return false;
	//
	///* Write jmp at second league_check */
	//if (!WriteJmp(reinterpret_cast<void*>(stub_dll + 0xCE70C6), reinterpret_cast<void*>(league2_check_hook), 16))
	//	return false;
	//
	///* Write jmp at third league_check */
	//if (!WriteJmp(reinterpret_cast<void*>(stub_dll + 0xCE70EF), reinterpret_cast<void*>(league3_check_hook), 16))
	//	return false;
	//
	///* Write jmp at fourth league_check */
	//if (!WriteJmp(reinterpret_cast<void*>(stub_dll + 0xCE7121), reinterpret_cast<void*>(league4_check_hook), 14))
	//	return false;


	//const uintptr_t stubCheck = stub + Offsets::StubCrcRoutine::STUB_CRC_ROUTINE_CHECK_FUNCTION;
	//HookManager::StubJmpAddress = stubCheck + 15;
	//if (!HookManager::WriteJmp(reinterpret_cast<void*>(stubCheck), reinterpret_cast<void*>(HookManager::HookStubCheck), 15))
	//	return false;
	//
	//const uintptr_t leagueFirstCheck = stub + Offsets::StubCrcRoutine::LEAGUE_1_CRC_ROUTINE_CHECK_FUNCTION;
	//HookManager::LeagueFirstJmpAddress = leagueFirstCheck + 14;
	//if (!HookManager::WriteJmp(reinterpret_cast<void*>(leagueFirstCheck), reinterpret_cast<void*>(HookManager::HookLeagueFirstCheck), 14))
	//	return false;
	//
	//const uintptr_t leagueSecondCheck = stub + Offsets::StubCrcRoutine::LEAGUE_2_CRC_ROUTINE_CHECK_FUNCTION;
	//HookManager::LeagueSecondJmpAddress = leagueSecondCheck + 16;
	//if (!HookManager::WriteJmp(reinterpret_cast<void*>(leagueSecondCheck), reinterpret_cast<void*>(HookManager::HookLeagueSecondCheck), 16))
	//	return false;
	//
	//const uintptr_t leagueThirdCheck = stub + Offsets::StubCrcRoutine::LEAGUE_3_CRC_ROUTINE_CHECK_FUNCTION;
	//HookManager::LeagueThirdJmpAddress = leagueThirdCheck + 16;
	//if (!HookManager::WriteJmp(reinterpret_cast<void*>(leagueThirdCheck), reinterpret_cast<void*>(HookManager::HookLeagueThirdCheck), 16))
	//	return false;
	//
	//const uintptr_t leagueFourthCheck = stub + Offsets::StubCrcRoutine::LEAGUE_4_CRC_ROUTINE_CHECK_FUNCTION;
	//HookManager::LeagueFourthJmpAddress = leagueFourthCheck + 14;
	//if (!HookManager::WriteJmp(reinterpret_cast<void*>(leagueFourthCheck), reinterpret_cast<void*>(HookManager::HookLeagueFourthCheck), 14))
	//	return false;
	//
	return true;
}

uintptr_t HookManager::GetShadowModule()
{
	//static uintptr_t shadowModule = 0;

		MEMORY_BASIC_INFORMATION64 mbi = { 0 };
		DWORD64 start = 0;
		DWORD64 result = 0;

		while (VirtualQuery(reinterpret_cast<LPVOID>(start), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&mbi), sizeof(MEMORY_BASIC_INFORMATION64)) != 0)
		{
			if (mbi.Protect & PAGE_READWRITE && mbi.State == MEM_COMMIT && mbi.Type == 0x40000)
			{
				result = mbi.AllocationBase;
				if (*reinterpret_cast<WORD*>(result) == 0x5A4D) {
					const auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(result);
					const auto ntPtr = reinterpret_cast<PIMAGE_NT_HEADERS64>(result + dosHeader->e_lfanew);

					if (ntPtr->FileHeader.NumberOfSections == 10)
						break;
				}
			}

			start += mbi.RegionSize;
		}

	return result;
}

bool HookManager::WriteJmp(void* address, void* destination, const size_t size)
{
	uint8_t jmpInstruction[14] = {
		0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	if (size < sizeof(jmpInstruction))
		return false;

	DWORD curprotect;
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &curprotect);

	C_HookManager::ByteMap::Insert(reinterpret_cast<uintptr_t>(address), size);

	*((DWORD64*)&jmpInstruction[6]) = reinterpret_cast<uintptr_t>(destination);
	memcpy(address, &jmpInstruction, sizeof(jmpInstruction));

	for (size_t i = sizeof(jmpInstruction); i < size; ++i)
		*reinterpret_cast<std::uint8_t*>((DWORD64)address + i) = 0x90;

	VirtualProtect(address, size, curprotect, 0);
	return true;
}

//__declspec(naked) void HookManager::HookStubCheck()
//{
//	__asm {
//		pushf
//		push rax
//		push rcx
//		push rdx
//		push r8
//
//		mov rcx, rax
//		call C_HookManager::ByteMap::FindKey
//		movzx esi, al
//
//		pop r8
//		pop rdx
//		pop rcx
//		pop rax
//		popf
//		cmp di, si
//		xor esi, r11d
//		and esi, 0x000000FF
//		jmp HookManager::StubJmpAddress
//	}
//}
//
//__declspec(naked) void HookManager::HookLeagueFirstCheck() {
//	__asm {
//		pushf
//		push rax
//		push rcx
//		push rdx
//		push rbx
//		push r8
//
//		add rbx, rcx
//		mov rcx, rbx
//		call C_HookManager::ByteMap::FindKey
//		movzx esi, al
//
//		pop r8
//		pop rbx
//		pop rdx
//		pop rcx
//		pop rax
//		popf
//		cmp r13b, al
//		xor rsi, rax
//		imul rsi, r15
//		jmp HookManager::LeagueFirstJmpAddress
//	}
//}
//
//__declspec(naked) void HookManager::HookLeagueSecondCheck() {
//	__asm {
//		pushf
//		push rcx
//		push rdx
//		push rbx
//		push r8
//
//		add rbx, rax
//		mov rcx, rbx
//		call C_HookManager::ByteMap::FindKey
//		movzx eax, al
//
//		pop r8
//		pop rbx
//		pop rdx
//		pop rcx
//		popf
//		cmovpe rbx, rbx
//		xor rax, rsi
//		shld esi, r14d,0x10
//		jmp HookManager::LeagueSecondJmpAddress
//	}
//}
//
//__declspec(naked) void HookManager::HookLeagueThirdCheck() {
//	__asm {
//		pushf
//		push rax
//		push rcx
//		push rdx
//		push rsi
//		push r8
//
//		add rsi, rbx
//		mov rcx, rsi
//		call C_HookManager::ByteMap::FindKey
//		movzx ebx, al
//
//		pop r8
//		pop rsi
//		pop rdx
//		pop rcx
//		pop rax
//		popf
//		btc si, r8w
//		inc sil
//		sbb sil, 14
//		jmp HookManager::LeagueThirdJmpAddress
//	}
//}
//
//__declspec(naked) void HookManager::HookLeagueFourthCheck() {
//	__asm {
//		pushf
//		push rcx
//		push rdx
//		push rsi
//		push r8
//
//		add rsi, rax
//		mov rcx, rsi
//		call C_HookManager::ByteMap::FindKey
//		movzx eax, al
//
//		pop r8
//		pop rsi
//		pop rdx
//		pop rcx
//		popf
//		stc
//		test r14d, 0x2665EC7
//		cmp dl, ah
//		jmp HookManager::LeagueFourthJmpAddress
//	}
//}

char HookManager::HookSendChat(uintptr_t chatInstance, const char* message, int a3)
{
	Logger::Warn("Message Sent: %s", message);
	return HookManager::OriginalSendChat(chatInstance, message, a3);
	//return 1;
}

