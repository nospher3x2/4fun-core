#include "NeutralCampManager.hpp"

GameObject* NeutralCampManager::GetCampObject(const CampId campId)
{
	static const auto fnFindCamp{
		reinterpret_cast<GameObject*(__fastcall*)(uintptr_t*, CampId)>(DEFINE_RVA(0x1F7D70))
	};

	return fnFindCamp(NeutralCampManager::GetInstance(), campId);
}

float NeutralCampManager::GetTimerExpiry(GameObject* camp)
{
	static const auto fnGetTimerExpiry{
		reinterpret_cast<float(__fastcall*)(GameObject*)>(DEFINE_RVA(0x2031B0))
	};

	return fnGetTimerExpiry(camp);
}

uintptr_t* NeutralCampManager::GetInstance()
{
	static uintptr_t* campManagerInstance{
		*reinterpret_cast<uintptr_t**>(DEFINE_RVA(0x21894F8))
	};

	return campManagerInstance;
}


