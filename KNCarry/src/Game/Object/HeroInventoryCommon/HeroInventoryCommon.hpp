#pragma once
#include <vector>
#include "InventorySlot/InventorySlot.hpp"

class HeroInventoryCommon
{
public:
	CLASS_GETTER(float, GetGold, 0x10)

	std::vector<InventorySlot*> GetItems();
	InventorySlot* GetItem(uint8_t slot);

	//bool CanUseItem();

	bool IsShopOpen();
	//void BuyItem(uint16_t itemId);
	//void SellItem(uint8_t slot);
	//void SwapItem(uint8_t slot1, uint8_t slot2);
	//void UndoItem();

	void ShowDebugImGuiMenu();
};

