#include "HeroInventoryCommon.hpp"
#include "../../../Drawing/ImGui/imgui.h"

bool HeroInventoryCommon::IsShopOpen()
{
	return *reinterpret_cast<bool*>(this + 0x209);
}

std::vector<InventorySlot*> HeroInventoryCommon::GetItems()
{
	std::vector<InventorySlot*> items{};
	for (uint8_t index = 0; index < 6; index++)
	{
		InventorySlot* item = *reinterpret_cast<InventorySlot**>(this + 0x30 + (index * 0x8));
		if (!item)
			continue;

		item->SetSlot(index + 6);
		items.push_back(item);
	}

	return items;
}

InventorySlot* HeroInventoryCommon::GetItem(const uint8_t slot)
{
	if (slot < 6 || slot > 11)
		return nullptr;

	InventorySlot* item = *reinterpret_cast<InventorySlot**>(this + 0x30 + (slot - 5) * 0x8);
	item->SetSlot(slot);
	return item;
}

void HeroInventoryCommon::ShowDebugImGuiMenu()
{
	ImGui::Text("Address: 0x%llX", this);
	ImGui::Text("Gold: %f", this->GetGold());
	ImGui::Text("Items:");
	ImGui::Indent();
	for (uint8_t index = 0; index < 6; index++)
	{
		InventorySlot* item = *reinterpret_cast<InventorySlot**>(this + 0x30 + index * 0x8);
		if (item == nullptr || !item->IsValid())
		{
			ImGui::Text("Index: %i - Empty, ", index);
			continue;
		}

		ImGui::Text("Address: 0x%llX", item);
		const uint16_t itemId = item->GetScriptBaseItem()->GetItemData()->GetItemId();
		if (ImGui::TreeNode(std::to_string(itemId).c_str(), "Id: %i - Slot: %i", itemId, index))
		{
			ImGui::Text("Address: 0x%llX", item);
			ImGui::Indent();
			ImGui::Text("Id: %i", itemId);
			ImGui::Text("Price: %f", item->GetScriptBaseItem()->GetPrice());
			ImGui::Text("Stacks: %f", item->GetScriptBaseItem()->GetStacks());
			ImGui::TreePop();
		}
	}
}
