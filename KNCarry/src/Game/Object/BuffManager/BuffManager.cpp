#include "BuffManager.hpp"

#include "../GameObject.hpp"
#include "../../../Riot/RiotHash.hpp"
#include "../../../Drawing/ImGui/imgui.h"

std::vector<BuffInstance*> BuffManager::GetBuffs() const
{
	const uintptr_t arrayBegin = this->GetArrayInstanceBegin();
	const uintptr_t arrayEnd = this->GetArrayInstanceEnd();

	if (arrayBegin == 0 || arrayEnd == 0)
		return {};
	
	std::vector<BuffInstance*> instances{};
	for (uintptr_t buffPtr = arrayBegin; buffPtr < arrayEnd; buffPtr += 0x10)
	{
		BuffInstance* buff = *reinterpret_cast<BuffInstance**>(buffPtr);
		if (buff == nullptr || !buff->IsActive())
			continue;

		instances.push_back(buff);
	}

	return instances;
}

BuffInstance* BuffManager::GetBuff(const uint32_t hash) const
{
	const uintptr_t arrayBegin = this->GetArrayInstanceBegin();
	const uintptr_t arrayEnd = this->GetArrayInstanceEnd();

	if (arrayBegin == 0 || arrayEnd == 0)
		return nullptr;

	for (uintptr_t buffPtr = arrayBegin; buffPtr < arrayEnd; buffPtr += 0x10)
	{
		BuffInstance* buff = *reinterpret_cast<BuffInstance**>(buffPtr);
		if (buff == nullptr || !buff->IsActive())
			continue;

		if (buff->GetHash() == hash)
			return buff;
	}

	return nullptr;
}

BuffInstance* BuffManager::GetBuff(const std::vector<uint32_t>& hashes) const
{
	const uintptr_t arrayBegin = this->GetArrayInstanceBegin();
	const uintptr_t arrayEnd = this->GetArrayInstanceEnd();

	if (arrayBegin == 0 || arrayEnd == 0)
		return nullptr;

	for (uintptr_t buffPtr = arrayBegin; buffPtr < arrayEnd; buffPtr += 0x10)
	{
				BuffInstance* buff = *reinterpret_cast<BuffInstance**>(buffPtr);
		if (buff == nullptr || !buff->IsActive())
			continue;

		for (const uint32_t hash : hashes)
		{
			if (buff->GetHash() == hash)
				return buff;
		}
	}

	return nullptr;
}

BuffInstance* BuffManager::GetBuffByType(const BuffType type) const
{
	const uintptr_t arrayBegin = this->GetArrayInstanceBegin();
	const uintptr_t arrayEnd = this->GetArrayInstanceEnd();

	if (arrayBegin == 0 || arrayEnd == 0)
		return nullptr;

	for (uintptr_t buffPtr = arrayBegin; buffPtr < arrayEnd; buffPtr += 0x10)
	{
		BuffInstance* buff = *reinterpret_cast<BuffInstance**>(buffPtr);
		if (buff == nullptr || !buff->IsActive())
			continue;

		if (buff->GetType() == type)
			return buff;
	}

	return nullptr;
}



void BuffManager::ShowDebugImGuiMenu() const
{
	const uintptr_t arrayBegin = this->GetArrayInstanceBegin();
	const uintptr_t arrayEnd = this->GetArrayInstanceEnd();

	if (arrayBegin == 0 || arrayEnd == 0)
	{
		ImGui::Text("BuffManager is not initialized");
		return;
	}

	ImGui::Text("Owner Address: 0x%llX", this->GetOwner());
	ImGui::Text("Owner Handle: %lu", this->GetOwnerHandle());
	ImGui::Text("Owner NetworkId: %lu", this->GetOwnerNetworkId());
	ImGui::Text("ArrayBegin: 0x%llX", arrayBegin);
	ImGui::Text("ArrayEnd: 0x%llX", arrayEnd);

	ImGui::Separator();

	ImGui::Text("Buffs:");
	ImGui::Indent();
	for (uintptr_t buffPtr = arrayBegin; buffPtr < arrayEnd; buffPtr += 0x10)
	{
		const BuffInstance* buff = *reinterpret_cast<BuffInstance**>(buffPtr);
		if (buff == nullptr || !buff->IsActive())
			continue;

		if (ImGui::TreeNode(buff->GetName(), "%s - %lu", buff->GetName(), buff->GetHash()))
		{
			ImGui::Text("Buff: 0x%llX", buff);
			ImGui::Indent();
			ImGui::Text("Name: %s", buff->GetName());
			ImGui::Text("Hash: 0x%08X", buff->GetHash());
			ImGui::Text("Type: %i", buff->GetType());
			ImGui::Text("StartTime: %f", buff->GetStartTime());
			ImGui::Text("EndTime: %f", buff->GetEndTime());
			if (buff->GetCasterNetworkId() > 0)
			{
				ImGui::Text("Caster NetworkId: %lu", buff->GetCasterNetworkId());
			}

			ImGui::Text("Count: %i", buff->GetCount());
			ImGui::Text("Stacks: %i", buff->GetStacks());
			ImGui::TreePop();
		}
	}
}
