#pragma once

#define STR_MERGE_IMPL(x, y)				x##y
#define STR_MERGE(x,y)						STR_MERGE_IMPL(x,y)
#define MAKE_PAD(size)						char STR_MERGE(pad_, __COUNTER__) [ size ]
#define DEFINE_MEMBER_0(x)				    x // y is for making it more readable
#define DEFINE_MEMBER_N(x,offset)			struct { MAKE_PAD(offset); x; }
#define CLASS_GETTER(returnType, name, offset) \
[[nodiscard]] inline returnType name() const \
{ \
	return *reinterpret_cast<returnType*>(std::uintptr_t(this) + offset); \
}

#include <WTypesbase.h>
#include <iomanip>
#include <iosfwd>
#include <Psapi.h>
#include <sstream>
#include <Windows.h>

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

	static inline uintptr_t BASE_ADDRESS{ uintptr_t(GetModuleHandle(nullptr)) };
	static inline MODULEINFO MODULE_INFO{ nullptr };
	static inline uintptr_t* SPOOF_TRAMPOLINE{ nullptr };

	static constexpr uintptr_t DEREF_POINTER{ 0x102A5f0 };
	static constexpr uintptr_t LOCAL_PLAYER{ 0x21A56F8 };
	static constexpr uintptr_t GAME_TIME{ 0x2198714 };

	static constexpr uintptr_t GET_SELECTED_ELEMENTAL_TERRAIN_FUNCTION{0x285E40};

	namespace MissionInfo
	{
		static constexpr uintptr_t INSTANCE{ 0x2189398 };
	}

	namespace R3DRenderer
	{
		static constexpr uintptr_t INSTANCE{ 0x21F50D0 };
		static constexpr uintptr_t WORLD_INSTANCE { 0x218C2E8 };
		static constexpr uintptr_t WORLD_INSTANCE_OFFSET { 0x270 };
		static constexpr uintptr_t WORLD_TO_SCREEN_FUNCTION{ 0xE017F0 };
	}

	namespace ObjectManager
	{
		static constexpr uintptr_t INSTANCE { 0x2189390 };
		static constexpr uintptr_t GET_OBJECT_BY_HANDLE_FUNCTION{ 0x3966E0 };
		static constexpr uintptr_t GET_OBJECT_BY_NETWORK_ID_FUNCTION{ 0x399A20 };
		static constexpr uintptr_t ON_CREATE_OBJECT_FUNCTION{ 0x0 };
		static constexpr uintptr_t ON_DELETE_OBJECT_FUNCTION{ 0x0 };

	}

	namespace ManagerTemplate
	{
		static constexpr uintptr_t HERO_MANAGER{ 0x21894B0 };
		static constexpr uintptr_t MINION_MANAGER{ 0x218C328 };
		static constexpr uintptr_t TURRET_MANAGER{ 0x2192BC0 };
		static constexpr uintptr_t INHIBITOR_MANAGER{ 0x21894C8 };
		static constexpr uintptr_t MISSILE_MANAGER{ 0x21A5780 };
	}


	namespace GameObject
	{
		static constexpr uintptr_t GET_GOLD_REDIRECT_TARGET_FUNCTION{ 0x1FDCB0 };
	}

	namespace Experience
	{
		static constexpr uintptr_t GET_AMOUNT_TO_NEXT_LEVEL_FUNCTION{ 0x273A20 };
		static constexpr uintptr_t GET_EXP_TO_GIVEN_LEVEL_FUNCTION{ 0x2809D0 };
	}

	namespace SpellDatabaseClient
	{
		static constexpr uintptr_t INSTANCE{ 0x21893F8 };
		static constexpr uintptr_t HAS_SPELL_DATA_FUNCTION{ 0x69F4A0 };
		static constexpr uintptr_t GET_SPELL_DATA_FUNCTION{ 0x695A90 };
	}
}

#define DEFINE_RVA(address) (Offsets::BASE_ADDRESS + address)
