#pragma once

#define STR_MERGE_IMPL(x, y)				x##y
#define STR_MERGE(x,y)						STR_MERGE_IMPL(x,y)
#define MAKE_PAD(size)						char STR_MERGE(pad_, __COUNTER__) [ size ]
#define DEFINE_MEMBER_0(x)				    x // y is for making it more readable
#define DEFINE_MEMBER_N(x,offset)			struct { MAKE_PAD(offset); x; }
#define CLASS_GETTER(returnType, name, offset) \
[[nodiscard]] returnType name() const \
{ \
	return *reinterpret_cast<returnType*>(std::uintptr_t(this) + offset); \
}

#include <WTypesbase.h>
#include <iomanip>
#include <iosfwd>
#include <sstream>
#include <Windows.h>

#include "../Utils/Memory/MemoyScanner.hpp"
template< typename T >
std::string hexify(T i)
{
	std::stringbuf buf;
	std::ostream os(&buf);


	os << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2)
		<< std::hex << i;

	return buf.str().c_str();
}

template <typename T, typename ... Args_t>
constexpr T CallVFunc(void* thisptr, size_t nIndex, Args_t... argList)
{
	using VirtualFn = T(__thiscall*)(void*, decltype(argList)...);
	return (*static_cast<VirtualFn**>(thisptr))[nIndex](thisptr, argList...);
}

namespace Offsets
{

	static const uintptr_t BASE_ADDRESS{ uintptr_t(GetModuleHandle(nullptr)) };
	static inline void* SPOOF_TRAMPOLINE{ MemoryScanner::ScanModInternal(
		"\xFF\x23", "xx", reinterpret_cast<char*>(GetModuleHandle(nullptr))
	)};

	static constexpr uintptr_t DEREF_POINTER{ 0x106C580 }; //E8 ?? ?? ?? ?? 48 8B C8 E8 ?? ?? ?? ?? 80 3B 00
	static constexpr uintptr_t LOCAL_PLAYER{ 0x21F6AC0 }; // 0F 84 68 01 00 00 48 89 5C 24 60
	static constexpr uintptr_t GAME_TIME{ 0x21E4948 }; // 0F 28 74 24 ? F3 0F 11 3D ? ? ? ?

	namespace StubCrcRoutine
	{
		static constexpr uintptr_t STUB_CRC_ROUTINE_CHECK_FUNCTION{ 0x97AEC7 }; // 0F B6 32 33 F1 84 C9 81 E6 FF 00 00 00 F5 8B 34 B0 C1 E9 08 E9 ?? ?? ?? ?? F9
		static constexpr uintptr_t LEAGUE_1_CRC_ROUTINE_CHECK_FUNCTION{ 0xCE70AA   }; // 0F B6 34 0B 48 31 C6
		static constexpr uintptr_t LEAGUE_2_CRC_ROUTINE_CHECK_FUNCTION{ 0xCE70C6  }; // F9 0F B6 04 03 
		static constexpr uintptr_t LEAGUE_3_CRC_ROUTINE_CHECK_FUNCTION{ 0xCE70EF  }; // 0F B6 1C 1E 
		static constexpr uintptr_t LEAGUE_4_CRC_ROUTINE_CHECK_FUNCTION{ 0xCE7121  }; // 0F B6 04 06 
	}

	namespace MissionInfo 
	{
		static constexpr uintptr_t INSTANCE{ 0x21DA228 }; // 48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 49 8D 8E 50 02 00 00
	}

	namespace R3DRenderer
	{
		static constexpr uintptr_t INSTANCE{ 0x2248930 }; // 48 8B 0D ?? ?? ?? ?? 4C 8D 44 24 50 48 8B D0 xref "DISABLE_FOW"
		static constexpr uintptr_t WORLD_INSTANCE { 0x21DD270 }; // 48 8B 3D ?? ?? ?? ?? FF 90
		static constexpr uintptr_t WORLD_INSTANCE_OFFSET { 0x270 };
		static constexpr uintptr_t WORLD_TO_SCREEN_FUNCTION{ 0xE36FC0 }; // 48 83 EC 38 49 8B C0 4C
	}

	namespace ObjectManager
	{
		static constexpr uintptr_t INSTANCE { 0x21DA220 }; // 48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B F0 48 85 C0 0F 84 8F 00 00 00
		static constexpr uintptr_t GET_OBJECT_BY_HANDLE_FUNCTION{ 0x3966E0 }; // 48 89 5C 24 10 55 56 57 41 56 41 57 48 83 EC 20 4C
		static constexpr uintptr_t GET_OBJECT_BY_NETWORK_ID_FUNCTION{ 0x399A20 }; // 3B 15 ?? ?? ?? ?? 74 44 4C 8B 41
		static constexpr uintptr_t ON_CREATE_OBJECT_FUNCTION{ 0x0 };
		static constexpr uintptr_t ON_DELETE_OBJECT_FUNCTION{ 0x0 };

	}

	namespace ManagerTemplate
	{
		static constexpr uintptr_t HERO_MANAGER{ 0x21DA340 }; // 48 8B 70 08 45 8D 7C 24 FF
		static constexpr uintptr_t MINION_MANAGER{ 0x21DD2B0 }; // 49 8B 78 08 41 8B 40 10 48 8D 0C C7 48 3B F9 73 47 48 39 1F 74 0B 48 83 C7 08 48 3B F9 72 F2 EB 37 48 83 C1 F8 48 3B F9 73 1E 48 2B CF 48 89 74 24 38 48 FF C9 48 8D 77 08 48 C1 E9 03 48 FF C1 F3 48 A5 48 8B 74 24 38 41 FF 48 10 48 8B D3 49 8B 00 49 8B C8 FF 50 ?? 48 8B 83 98 04 00 00
		static constexpr uintptr_t TURRET_MANAGER{ 0x21E3BC0 }; // 48 89 0D ?? ?? ?? ?? 48 8D 05 ?? ?? ?? ?? 33 D2 48 89 01 48 8B C1
		static constexpr uintptr_t INHIBITOR_MANAGER{ 0x21F6DB8 }; // idk
		static constexpr uintptr_t BUILDING_MANAGER{ 0x21A5AE8 }; // idk
		static constexpr uintptr_t MISSILE_MANAGER{ 0x21F6BC0 }; // 49 8B 58 08 49 8D 70 08
	}

	namespace GameObject
	{
		static constexpr uintptr_t GET_PATH_CONTROLLER_COMMON_FUNCTION{ 0x208420 }; // E8 ? ? ? ? 44 39 60 08 
	}

	namespace Spellbook
	{
		static constexpr uintptr_t INSTANCE{ 0x2A00 }; // E8 ? ? ? ? 84 C0 0F 85 ? ? ? ? 48 8B 0D ? ? ? ? 48 81 C1 ? ? ? ?
		static constexpr uintptr_t ACTIVE_SPELL{ 0x38 }; // not tested

		static constexpr uintptr_t SPELLS{ 0x6D0 }; // 83 FA 3F 77 0C 
		static constexpr uintptr_t GET_MANA{ 0x90 }; // idk, not tested.
	}

	namespace Experience
	{
		static constexpr uintptr_t GET_AMOUNT_TO_NEXT_LEVEL_FUNCTION{ 0x27AFF0 }; // 40 57 48 83 EC 30 0F 29 74 24 20 48
		static constexpr uintptr_t GET_EXP_TO_GIVEN_LEVEL_FUNCTION{ 0x288140 }; // 48 89 5C 24 10 56 48 83 EC 20 8B DA
	}

	namespace SpellDatabaseClient
	{
		static constexpr uintptr_t INSTANCE{ 0x21B73E8 }; // 48 83 C1 08 E8 ?? ?? ?? ?? 48 83 7C 24 38 00
		static constexpr uintptr_t GET_SPELL_DATA_FUNCTION{ 0x69C9D0 }; // 48 8D 4F 08 E8 ? ? ? ? E9 ? ? ? ? 48 85 F6 
	}
}

#define DEFINE_RVA(address) (Offsets::BASE_ADDRESS + address)

static int FindVFunc(const DWORD64& object, const DWORD64& address)
{
	DWORD64* base = *reinterpret_cast<DWORD64**>(object);
	int i = 0;
	while (base && base[i])
	{
		if ((base[i] - Offsets::BASE_ADDRESS) == address)
		{
			return i;
		}
		i++;
	}
	return -1;
}