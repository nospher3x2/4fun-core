#pragma warning(disable : 4996)

#define WIN32_LEAN_AND_MEAN
#include <chrono>
#include <windows.h>

#include "./src/Drawing/DrawManager.hpp"
#include "./src/Game/R3DRenderer/R3DRenderer.hpp"

#include "./src/EventHandler/EventHandler.hpp"
#include "./src/Logger/Logger.hpp"
#include "src/Plugins/PluginManager.hpp"


//struct Pair
//{
//	DWORD64 Key;
//	BYTE  Value;
//};
//inline std::vector<Pair> Pairs {};
//
////inline std::vector<Pair> Pairs = {};
//class C_HookManager
//{
//public:
//	class ByteMap {
//	public:
//
//		inline static void Insert(DWORD64 hookAddress, size_t hookSize) {
//			for (int i = 0; i <= hookSize; i++) {
//				//Pairs.insert({ hookAddress + i, *(BYTE*)(hookAddress + i) });
//				Pairs.insert(Pairs.end(), { hookAddress + i, *(BYTE*)(hookAddress + i) });
//			}
//		}
//
//		inline static DWORD64 FindKey(DWORD64 currentAddress) {
//			//if (Pairs.find(currentAddress) != Pairs.end())
//			//	return Pairs[currentAddress];
//
//			for (std::size_t i = 0; i <= Pairs.size(); ++i) {
//				if (Pairs[i].Key == currentAddress)
//					return Pairs[i].Value;
//			}
//			return *(BYTE*)(currentAddress);
//		}
//
//		ByteMap() {}
//	};
//};
//
//uintptr_t stub_jmp_address;
//__declspec(naked) void stub_check_hook() {
//	__asm {
//		pushf
//		push rax
//		push rcx
//		push rdx
//		push r8
//
//		mov rcx, rax
//		call HookManager::GetSpoofedBytes
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
//		jmp stub_jmp_address
//	}
//}
//
//uintptr_t league1_jmp_address;
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
//		call HookManager::GetSpoofedBytes
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
//		jmp league1_jmp_address
//	}
//}
//
//uintptr_t league2_jmp_address;
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
//		call HookManager::GetSpoofedBytes
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
//		jmp league2_jmp_address
//	}
//}
//
//uintptr_t league3_jmp_address;
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
//		call HookManager::GetSpoofedBytes
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
//		jmp league3_jmp_address
//	}
//}
//
//uintptr_t league4_jmp_address;
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
//		call HookManager::GetSpoofedBytes
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
//		jmp league4_jmp_address
//	}
//}
//
//bool writejmp(void* address, void* destination, size_t size)
//{
//	uint8_t jmpInstruction[14] = {
//		0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
//		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//	};
//
//	if(size < sizeof(jmpInstruction))
//		return false;
//
//	DWORD curprotect;
//	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &curprotect);
//
//	HookManager::SaveOriginalByte(reinterpret_cast<uintptr_t>(address), size);
//
//	*((DWORD64*)&jmpInstruction[6]) = reinterpret_cast<uintptr_t>(destination);
//	memcpy(address, &jmpInstruction, sizeof(jmpInstruction));
//
//	for (size_t i = sizeof(jmpInstruction); i < size; ++i)
//		*reinterpret_cast<std::uint8_t*>((DWORD64)address + i) = 0x90;
//
//	VirtualProtect(address, size, curprotect, 0);
//	return true;
//}

//
////static int FindVFuncx(const DWORD64& object, const DWORD64& address)
////{
////	DWORD64* base = *reinterpret_cast<DWORD64**>(object);
////	int i = 0;
////	while (base && base[i])
////	{
////		Logger::Warn("Trying %i", i);
////		if ((base[i] - Offsets::BASE_ADDRESS) == address)
////		{
////			return i;
////		}
////		i++;
////	}
////	return -1;
////}
////
//bool hook_bypass()
//{
//	/* Get address of stub.dll */
//	DWORD64 stub_dll = (DWORD64)GetModuleHandle(L"stub.dll");
//
//	/* Check if stub.dll is loaded */
//	if (!stub_dll) {
//		return false;
//	}
//
//	stub_jmp_address = stub_dll + 0x97AEC7 + 15;
//	league1_jmp_address = stub_dll + 0xCE70AA + 14;
//	league2_jmp_address = stub_dll + 0xCE70C6 + 16;
//	league3_jmp_address = stub_dll + 0xCE70EF + 16;
//	league4_jmp_address = stub_dll + 0xCE7121 + 14;
//
//	/* Write jmp at stub_check */
//	if (!writejmp(reinterpret_cast<void*>(stub_dll + 0x97AEC7), reinterpret_cast<void*>(stub_check_hook), 15))
//		return false;
//
//	/* Write jmp at first league_check */
//	if (!writejmp(reinterpret_cast<void*>(stub_dll + 0xCE70AA), reinterpret_cast<void*>(league1_check_hook), 14))
//		return false;
//
//	/* Write jmp at second league_check */
//	if (!writejmp(reinterpret_cast<void*>(stub_dll + 0xCE70C6), reinterpret_cast<void*>(league2_check_hook), 16))
//		return false;
//
//	/* Write jmp at third league_check */
//	if (!writejmp(reinterpret_cast<void*>(stub_dll + 0xCE70EF), reinterpret_cast<void*>(league3_check_hook), 16))
//		return false;
//
//	/* Write jmp at fourth league_check */
//	if (!writejmp(reinterpret_cast<void*>(stub_dll + 0xCE7121), reinterpret_cast<void*>(league4_check_hook), 14))
//		return false;
//
//	return true;
//}

int entrypoint()
{
	Logger::Initialize();
	DrawManager::Initialize();
	R3DRenderer::Initialize();
	PluginManager::Initialize();

	return 1;
}

__declspec(safebuffers)BOOL APIENTRY DllMain(const HMODULE hModule, const DWORD reason, [[maybe_unused]] LPVOID reserved)
{
	if (reason != DLL_PROCESS_ATTACH)
		return false;

	entrypoint();
	return true;
}
