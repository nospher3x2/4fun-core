#pragma once
#include "../../../Patchables/Offsets.hpp"
 
class Experience
{
public:
	CLASS_GETTER(float, GetTotalExperience, 0x0)
	CLASS_GETTER(uint8_t, GetLevel, 0x18)
	CLASS_GETTER(uint8_t, GetSpellTrainingPoints, 0x58)

	float GetAmountToNextLevel()
	{
		static const auto fnGetAmountToNextLevel{
			reinterpret_cast<float(__fastcall*)(Experience*)>(DEFINE_RVA(Offsets::Experience::GET_AMOUNT_TO_NEXT_LEVEL_FUNCTION))
		};

		return fnGetAmountToNextLevel(this);
	}

	float GetExpToGivenLevel(const uint8_t level)
	{
		static const auto fnGetExpToGivenLevel{
			reinterpret_cast<float(__fastcall*)(Experience*, uint8_t)>(DEFINE_RVA(Offsets::Experience::GET_EXP_TO_GIVEN_LEVEL_FUNCTION))
		};

		return fnGetExpToGivenLevel(this, level);
	}
};