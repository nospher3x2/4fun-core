#pragma once
#include "../../../../Patchables/Offsets.hpp"
#include "../ScriptBaseItem/ScriptBaseItem.hpp"

class InventorySlot
{
public:
	CLASS_GETTER(ScriptBaseItem*, GetScriptBaseItem, 0x10)

	[[nodiscard]] bool IsValid() const
	{
		const ScriptBaseItem* item = GetScriptBaseItem();
		return item && item->GetItemData();
	}

	[[nodiscard]] uint8_t GetSlot() const
	{
		return Slot;
	}

	void SetSlot(const uint8_t slot)
	{
		this->Slot = slot;
	}
private:
	uint8_t Slot = -1;
};