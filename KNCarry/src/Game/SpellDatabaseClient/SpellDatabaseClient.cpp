#include "SpellDatabaseClient.hpp"

bool SpellDatabaseClient::HasData(const uint32_t hash)
{
	static const auto fnHasSpellData{
		reinterpret_cast<bool(__fastcall*)(const uintptr_t*, uint32_t)>(DEFINE_RVA(Offsets::SpellDatabaseClient::HAS_SPELL_DATA_FUNCTION))
	};

	return fnHasSpellData(SpellDatabaseClient::GetInstance(), hash);
}

SpellData* SpellDatabaseClient::GetData(const uint32_t hash)
{
	static const auto fnGetSpellData{
		reinterpret_cast<SpellData * (__fastcall*)(uintptr_t*, uint32_t)>(DEFINE_RVA(Offsets::SpellDatabaseClient::GET_SPELL_DATA_FUNCTION))
	};

	return fnGetSpellData(SpellDatabaseClient::GetInstance(), hash);
}

uintptr_t* SpellDatabaseClient::GetInstance()
{
	static auto spellDatabaseClient{
		reinterpret_cast<uintptr_t*>(
			*reinterpret_cast<uintptr_t*>(DEFINE_RVA(Offsets::SpellDatabaseClient::INSTANCE))
			+ 0x8
		)
	};

	return spellDatabaseClient;
}
