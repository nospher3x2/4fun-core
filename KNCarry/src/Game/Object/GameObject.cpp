#include "GameObject.hpp"
#include "../../Riot/RiotEncryption.hpp"
#include "../Game.hpp"

CharacterIntermediate* GameObject::GetCharacterIntermediate() const
{
	return reinterpret_cast<CharacterIntermediate*>(reinterpret_cast<uintptr_t>(this) + 0x19E8);
}

BuffManager* GameObject::GetBuffManager() const
{
	return reinterpret_cast<BuffManager*>(reinterpret_cast<uintptr_t>(this) + 0x27C0);
}

SpellbookClient* GameObject::GetSpellbook() const
{
	return reinterpret_cast<SpellbookClient*>(reinterpret_cast<uintptr_t>(this) + Offsets::Spellbook::INSTANCE);
}

Experience* GameObject::GetExperience() const
{
	return reinterpret_cast<Experience*>(reinterpret_cast<uintptr_t>(this) + 0x3FB8);
}

HeroInventoryCommon* GameObject::GetHeroInventoryCommon() const
{
	return reinterpret_cast<HeroInventoryCommon*>(reinterpret_cast<uintptr_t>(this) + 0x4018);
}

PathControllerCommon* GameObject::GetPathControllerCommon()
{
	const uintptr_t encryptedAddress = reinterpret_cast<uintptr_t>(this) + 0x3700;
	const byte v3b = *reinterpret_cast<byte*>(encryptedAddress + 16);
	
	const uint64_t v5 = *reinterpret_cast<uint64_t*>(encryptedAddress + 8);
	uint64_t v7 = *reinterpret_cast<uint64_t*>(encryptedAddress + (8 * v3b + 24));
	v7 ^= ~v5;
	
	return *reinterpret_cast<PathControllerCommon**>(v7 + 16);
}

GameObject* GameObject::GetGoldRedirectTarget()
{
	return CallVFunc<GameObject*>(this, 470);
}

bool GameObject::IsZombie() const
{
	return reinterpret_cast<RiotEncryption<bool>*>(reinterpret_cast<uintptr_t>(this) + 0x2A)->Decrypt();
}

uint32_t GameObject::GetTypeFlags() const
{
	return reinterpret_cast<RiotEncryption<uint32_t>*>(reinterpret_cast<uintptr_t>(this) + 0x40)->Decrypt();
}

bool GameObject::IsOnScreen() const
{
	return reinterpret_cast<RiotEncryption<bool>*>(reinterpret_cast<uintptr_t>(this) + 0x1E8)->Decrypt();
}

bool GameObject::IsDead() const
{
	return reinterpret_cast<RiotEncryption<bool>*>(reinterpret_cast<uintptr_t>(this) + 0x274)->Decrypt();
}

bool GameObject::CompareObjectTypeFlag(const ObjectTypeFlag flag) const
{
	return int(this->GetTypeFlags() & uint32_t(flag)) != 0;
}

void* GameObject::GetCircleIconPortrait() const
{
	static const auto fnGetCircleIconPortrait{
		reinterpret_cast<void* (__fastcall*)(const GameObject*)>
		(DEFINE_RVA(0x1FDCB0)) // E8 ?? ?? ?? ?? EB 13 8B 53 14
	};

	return fnGetCircleIconPortrait(this);
}

void* GameObject::GetSquareIconPortrait() const
{
	static const auto fnGetSquareIconPortrait{
		reinterpret_cast<void* (__fastcall*)(const GameObject*)>
		(DEFINE_RVA(0x2035A0)) // E8 ?? ?? ?? ?? EB 13 8B 53 14
	};

	return fnGetSquareIconPortrait(this);
}

float GameObject::GetBoundingRadius()
{
	return CallVFunc<float>(this, 37);
}

float GameObject::GetDeathDuration()
{
	return CallVFunc<float>(this, 236);
}

float GameObject::GetRespawnTimeRemaining()
{
	return CallVFunc<float>(this, 237);
}

bool GameObject::IsRecalling() const
{
	return this->GetRecallState() == 6 || this->GetRecallState() == 11;
}

bool GameObject::IsMe() const
{
	return this == Game::GetPlayer();
}

bool GameObject::IsAlly(const GameObject* other) const
{
	if (!other)
		other = Game::GetPlayer();

	return this->GetTeam() == other->GetTeam();
}

bool GameObject::IsEnemy(const GameObject* other) const
{
	return !this->IsAlly(other);
}

bool GameObject::IsAI() const
{
	return this->CompareObjectTypeFlag(ObjectTypeFlag::AI);
}

bool GameObject::IsMinion() const
{
	return this->CompareObjectTypeFlag(ObjectTypeFlag::AIMinionClient);
}

bool GameObject::IsHero() const
{
	return this->CompareObjectTypeFlag(ObjectTypeFlag::AIHeroClient);
}

bool GameObject::IsTurret() const
{
	return this->CompareObjectTypeFlag(ObjectTypeFlag::AI) && this->CompareObjectTypeFlag(ObjectTypeFlag::AITurretClient);
}

bool GameObject::IsMissile() const
{
	return this->CompareObjectTypeFlag(ObjectTypeFlag::MissileClient);
}

bool GameObject::IsBuilding() const
{
	return this->CompareObjectTypeFlag(ObjectTypeFlag::AnimatedBuilding);
}

bool GameObject::IsAttackableUnit() const
{
	return this->CompareObjectTypeFlag(ObjectTypeFlag::AttackableUnit);
}

bool GameObject::IsEffectEmitter() const
{
	return this->CompareObjectTypeFlag(ObjectTypeFlag::EffectEmitter);
}

bool GameObject::IsMelee() const
{
	return this->GetCombatType() == CombatType::Melee;
}

bool GameObject::IsRanged() const
{
	return this->GetCombatType() == CombatType::Ranged;
}

bool GameObject::CanCast() const
{
	return int(this->GetActionState() & ActionState::CanCast) != 0;
}

bool GameObject::CanMove() const
{
	return int(this->GetActionState() & ActionState::CanMove) != 0;
}

bool GameObject::CanAttack() const
{
	return int(this->GetActionState() & ActionState::CanAttack) != 0;
}

bool GameObject::IsAttackable(const bool ignoreAlly) const
{
	if (ignoreAlly && this->IsAlly())
		return false;

	if (!this->IsAI() && !this->IsBuilding())
		return false;

	if (this->IsDead() || (this->IsHero() && this->IsZombie()) || !this->IsVisible())
		return false;

	if (!this->IsTargetable() || int(this->GetStatusFlag() & StatusFlag::Invulnerable) != 0)
		return false;

	return !ignoreAlly && int(this->IsTargetableToTeamFlags() & 2) != 0;
}

float GameObject::GetDistanceSqrt(const GameObject* object) const
{
	return this->GetPosition().GetDistanceSqrt(object->GetPosition());
}

float GameObject::GetDistanceSqrt(const Vector3& position) const
{
	return this->GetPosition().GetDistanceSqrt(position);
}

float GameObject::GetDistance(const GameObject* object) const
{
	return this->GetPosition().GetDistance(object->GetPosition());
}

float GameObject::GetDistance(const Vector3& position) const
{
	return this->GetPosition().GetDistance(position);
}

float GameObject::GetRealAttackRange()
{
	return this->GetCharacterIntermediate()->GetAttackRange() + this->GetBoundingRadius();
}

void GameObject::ShowDebugImGuiMenu()
{
	ImGui::Text("Address: 0x%12p", this);
	ImGui::Text("Handle: %i", this->GetHandle());
	ImGui::Text("NetworkId: %i", this->GetNetworkId());
	ImGui::Text("Name: %s", this->GetName().c_str());
	ImGui::Text("Team: %i", this->GetTeam());
	ImGui::Text("Flags: %lu", this->GetTypeFlags());
	ImGui::Text("Position: %f, %f, %f", this->GetPosition().x, this->GetPosition().y, this->GetPosition().z);
	ImGui::Text("Is Visible: %s", this->IsVisible() ? "true" : "false");
	ImGui::Text("Is Zombie: %s", this->IsZombie() ? "true" : "false");
	ImGui::Text("Is On Screen: %s", this->IsOnScreen() ? "true" : "false");
	ImGui::Text("Is Dead: %s", this->IsDead() ? "true" : "false");

	if (ImGui::TreeNode("Object Stats"))
	{
		if (this->IsPAREnabled())
		{
			ImGui::Text("PAR: %f", this->GetPAR());
			ImGui::Text("Max PAR: %f", this->GetMaxPAR());
		}
		if (this->IsSAREnabled())
		{
			ImGui::Text("SAR: %f", this->GetSAR());
			ImGui::Text("Max SAR: %f", this->GetMaxSAR());
		}
		ImGui::Text("Status Flag: %i", this->GetStatusFlag());
		ImGui::Text("Lifetime: %f", this->GetLifetime());
		ImGui::Text("Lifetime Ticks: %f", this->GetLifetimeTicks());
		ImGui::Text("Is Targetable: %s", this->IsTargetable() ? "true" : "false");
		ImGui::Text("Is Targetable to Team Flags: %lu", this->IsTargetableToTeamFlags());
		ImGui::Text("Recall State: %i", this->GetRecallState());
		ImGui::Text("Health: %f", this->GetHealth());
		ImGui::Text("Max Health: %f", this->GetMaxHealth());
		ImGui::Text("All Shield: %f", this->GetAllShield());
		ImGui::Text("Physical Shield: %f", this->GetPhysicalShield());
		ImGui::Text("Magical Shield : %f", this->GetMagicalShield());
		ImGui::Text("Champ Specific Health : %f", this->GetChampSpecificHealth());
		ImGui::Text("Incoming Healing Allied: %f", this->GetIncomingHealingAllied());
		ImGui::Text("Incoming Healing Enemy: %f", this->GetIncomingHealingEnemy());
		ImGui::Text("Incoming Damage: %f", this->GetIncomingDamage());
		ImGui::Text("Stop Shield Fade: %f", this->GetStopShieldFade());
		ImGui::Text("State: %lu", this->GetActionState());
		ImGui::Text("State2: %lu", this->GetActionState2());
		ImGui::Text("Gold Total: %f", this->GetGoldTotal());
		ImGui::Text("Minimum Gold: %f", this->GetMinimumGold());
		ImGui::Text("Combat Type: %i", this->GetCombatType());
		if (ImGui::TreeNode("Character Data"))
		{
			ImGui::Text("Skin Name: %s", this->GetCharacterData()->GetSkinName());
			ImGui::Text("Skin Name: %lu", this->GetCharacterData()->GetSkinHash());
			ImGui::TreePop();
		}
		ImGui::Text("Num Neutral Minions Killed: %f", this->GetNumNeutralMinionsKilled());
		ImGui::Text("Vision Score: %f", this->GetVisionScore());
		ImGui::Text("Shutdown Value: %f", this->GetShutdownValue());
		ImGui::Text("Base Gold Given On Death: %f", this->GetBaseGoldGivenOnDeath());
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Character Intermediate"))
	{
		this->GetCharacterIntermediate()->ShowDebugImGuiMenu();
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Buff Manager"))
	{
		this->GetBuffManager()->ShowDebugImGuiMenu();
		ImGui::TreePop();
	}

	if (this->IsHero() && ImGui::TreeNode("Avatar Client"))
	{
		this->GetAvatarClient()->ShowDebugImGuiMenu();
		ImGui::TreePop();
	}

	if (this->IsHero() && ImGui::TreeNode("Hero Inventory Common"))
	{
		this->GetHeroInventoryCommon()->ShowDebugImGuiMenu();
		ImGui::TreePop();
	}
}
