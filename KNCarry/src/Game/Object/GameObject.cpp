#include "GameObject.hpp"

CharacterIntermediate* GameObject::GetCharacterIntermediate()
{
	return reinterpret_cast<CharacterIntermediate*>(reinterpret_cast<uintptr_t>(this) + 0x19D8);
}

SpellbookClient* GameObject::GetSpellbook()
{
	return reinterpret_cast<SpellbookClient*>(reinterpret_cast<uintptr_t>(this) + 0x29E8);
}

Experience* GameObject::GetExperience()
{
	return reinterpret_cast<Experience*>(reinterpret_cast<uintptr_t>(this) + 0x3FB0);
}

float GameObject::GetRealAttackRange()
{
	return this->GetCharacterIntermediate()->GetAttackRange() + this->GetBoundingRadius();
}

bool GameObject::IsAlive()
{
	static const auto fnIsAlive{
		reinterpret_cast<bool(__fastcall*)(GameObject*)>
		(DEFINE_RVA(0x243b50))
	};

	return fnIsAlive(this);
}

float GameObject::GetBoundingRadius()
{
	return CallVFunc<float>(this, 36);
}

GameObject* GameObject::GetGoldRedirectTarget()
{
	static const auto fnGetGoldRedirectTarget{
		reinterpret_cast<GameObject* (__fastcall*)(GameObject*)>
		(DEFINE_RVA(Offsets::GameObject::GET_GOLD_REDIRECT_TARGET_FUNCTION))
	};

	return fnGetGoldRedirectTarget(this);
}

void* GameObject::GetCircleIconPortrait()
{
	static const auto fnGetCircleIconPortrait{
		reinterpret_cast<void* (__fastcall*)(GameObject*)>
		(DEFINE_RVA(0x1FDCB0))
	};


	return fnGetCircleIconPortrait(this);
}
