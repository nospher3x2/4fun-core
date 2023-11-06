#pragma once
#include <cstdint>
#include <vector>

#include "./Perk/Perk.hpp"

class AvatarClient
{
public:
	[[nodiscard]] std::vector<Perk*> GetPerks() const;
	[[nodiscard]] Perk* GetPerk(PerkId id) const;

	void ShowDebugImGuiMenu() const;
private:
	static constexpr uint16_t MaxPerkSize = 0x480; // 9 runes
};

