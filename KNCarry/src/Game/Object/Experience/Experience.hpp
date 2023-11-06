#pragma once
#include "../../../Patchables/Offsets.hpp"

class Experience
{
public:
	CLASS_GETTER(float, GetTotalExperience, 0x0)
	CLASS_GETTER(uint8_t, GetLevel, 0x18)
	CLASS_GETTER(uint8_t, GetSpellTrainingPoints, 0x58)

	[[nodiscard]] float GetAmountToNextLevel() const
	{
		static const auto fnGetAmountToNextLevel{
			reinterpret_cast<float(__fastcall*)(const Experience*)>(DEFINE_RVA(Offsets::Experience::GET_AMOUNT_TO_NEXT_LEVEL_FUNCTION))
		};

		return fnGetAmountToNextLevel(this);
	}

	[[nodiscard]] float GetExpToGivenLevel(const uint8_t level) const
	{
		static const auto fnGetExpToGivenLevel{
			reinterpret_cast<float(__fastcall*)(const Experience*, uint8_t)>(DEFINE_RVA(Offsets::Experience::GET_EXP_TO_GIVEN_LEVEL_FUNCTION))
		};

		return fnGetExpToGivenLevel(this, level);
	}
};