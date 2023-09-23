#include "./SpellDataInstance.hpp"
#include "../../../Game.hpp"
#include "../../../../Logger/Logger.hpp"

bool SpellDataInstance::Cast()
{
	static const auto fnHudCastSpell{
		reinterpret_cast<void(__fastcall*)(uintptr_t*, ::SpellData*)>(DEFINE_RVA(0x897870))
	};

	::TargetClient* targetClient = this->GetTargetClient();
	if (!targetClient)
		return false;

	const GameObject* player = Game::GetPlayer();
	targetClient->CasterHandle = player->GetHandle();
	targetClient->TargetHandle = 0;
	targetClient->StartPosition = player->GetPosition();
	targetClient->EndPosition = player->GetPosition();
	targetClient->CursorPosition = player->GetPosition();
	targetClient->UnknownPosition = player->GetPosition();

	fnHudCastSpell(this->GetHudSpellLogic(), this->GetSpellData());
	return true;
}

bool SpellDataInstance::Cast(GameObject* target)
{
	static const auto fnHudCastSpell{
		reinterpret_cast<void(__fastcall*)(uintptr_t*, ::SpellData*)>(DEFINE_RVA(0x897870))
	};

	::TargetClient* targetClient = this->GetTargetClient();
	if (!targetClient)
		return false;

	const GameObject* player = Game::GetPlayer();
	targetClient->CasterHandle = player->GetHandle();
	targetClient->TargetHandle = target->GetHandle();
	targetClient->StartPosition = player->GetPosition();
	targetClient->EndPosition = target->GetPosition();
	targetClient->CursorPosition = target->GetPosition();
	targetClient->UnknownPosition = target->GetPosition();

	fnHudCastSpell(this->GetHudSpellLogic(), this->GetSpellData());
	return true;
}

bool SpellDataInstance::Cast(const Vector3& position)
{
	static const auto fnHudCastSpell{
		reinterpret_cast<void(__fastcall*)(uintptr_t*, ::SpellData*)>(DEFINE_RVA(0x897870))
	};

	TargetClient* targetClient = this->GetTargetClient();
	if (!targetClient)
		return false;

	const GameObject* player = Game::GetPlayer();
	targetClient->CasterHandle = player->GetHandle();
	targetClient->TargetHandle = 0;
	targetClient->StartPosition = player->GetPosition();
	targetClient->EndPosition = position;
	targetClient->CursorPosition = position;
	targetClient->UnknownPosition = position;

	fnHudCastSpell(nullptr, this->GetSpellData());
	return true;

}

bool SpellDataInstance::Cast(const Vector3& startPosition, const Vector3& endPosition)
{
	static const auto fnHudCastSpell{
		reinterpret_cast<void(__fastcall*)(uintptr_t*, ::SpellData*)>(DEFINE_RVA(0x897870))
	};

	TargetClient* targetClient = this->GetTargetClient();
	if (!targetClient)
		return false;

	const GameObject* player = Game::GetPlayer();
	targetClient->CasterHandle = player->GetHandle();
	targetClient->TargetHandle = 0;
	targetClient->StartPosition = startPosition;
	targetClient->EndPosition = endPosition;
	targetClient->CursorPosition = endPosition;
	targetClient->UnknownPosition = endPosition;

	fnHudCastSpell(this->GetHudSpellLogic(), this->GetSpellData());
	return true;
}

void SpellDataInstance::ShowDebugMessage() const
{
	Logger::Warn("-----------------");
	Logger::Warn("SpellDataInstance - Debug Message");
	Logger::Warn("Name: %s", this->GetSpellData()->GetName().c_str());
	Logger::Warn("Hash: %lu", this->GetSpellData()->GetHash());
	Logger::Warn("Level: %i", this->GetLevel());
	Logger::Warn("Expire Time: %.2f", this->GetExpireTime());
	Logger::Warn("Ammo: %i", this->GetAmmo());
	Logger::Warn("-----------------");
}


uintptr_t* SpellDataInstance::GetHudSpellLogic()
{
	static uintptr_t* hudManagerInputLogic = *reinterpret_cast<uintptr_t**>(DEFINE_RVA(0x21893A0 + 0x68));
	return hudManagerInputLogic;
}
