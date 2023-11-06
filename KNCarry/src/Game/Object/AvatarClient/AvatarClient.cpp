#include "AvatarClient.hpp"
#include "../../../Drawing/ImGui/imgui.h"

std::vector<Perk*> AvatarClient::GetPerks() const
{
	std::vector<Perk*> perks {};
	for (uint16_t i = 0; i <= AvatarClient::MaxPerkSize; i += 0x90)
	{
		Perk* perk = *reinterpret_cast<Perk**>(reinterpret_cast<uintptr_t>(this) + i);
		if (perk == nullptr)
			continue;

		perks.push_back(perk);
	}
	
	return perks;
}

Perk* AvatarClient::GetPerk(const PerkId id) const
{
	for (uint16_t i = 0; i <= AvatarClient::MaxPerkSize; i += 0x90)
	{
		Perk* perk = *reinterpret_cast<Perk**>(reinterpret_cast<uintptr_t>(this) + i);
		if (perk == nullptr || perk->GetId() != id)
			continue;

		return perk;
	}

	return nullptr;
}

void AvatarClient::ShowDebugImGuiMenu() const
{
	ImGui::Text("Perks:");
	ImGui::Indent();
	for (uint16_t i = 0; i <= AvatarClient::MaxPerkSize; i += 0x90)
	{
		const Perk* perk = *reinterpret_cast<Perk**>(reinterpret_cast<uintptr_t>(this) + i);
		if (perk == nullptr)
			continue;

		ImGui::Text("[%i] %s", perk->GetId(), perk->GetDisplayName());
	}
}

