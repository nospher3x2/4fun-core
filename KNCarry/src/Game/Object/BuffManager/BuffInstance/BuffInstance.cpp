#include "BuffInstance.hpp"
#include "../../../Game.hpp"

const char* BuffInstance::GetName() const
{
	return this->GetScriptBase()->GetName();
}

uint32_t BuffInstance::GetHash() const
{
	return this->GetScriptBase()->GetHash();
}

GameObject* BuffInstance::GetOwner() const
{
	return this->GetOwnerBuffManager()->GetOwner();
}

bool BuffInstance::IsActive() const
{
	return *reinterpret_cast<const BYTE*>(this + 0x38) && *reinterpret_cast<const int64_t*>(this + 0x10)
		|| *reinterpret_cast<const BYTE*>(this + 0x88);
}