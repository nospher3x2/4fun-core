#pragma once
#include "../../../../Riot/RiotString.hpp"
#include "../../../../Patchables/Offsets.hpp"
#include "../../../../Math/Vector.h"
#include "../../../../Logger/Logger.hpp"

class TargetClient
{
public:
	union
	{
		DEFINE_MEMBER_N(uint32_t CasterHandle, 0x10);
		DEFINE_MEMBER_N(uint32_t TargetHandle, 0x14);
		DEFINE_MEMBER_N(Vector3 StartPosition, 0x18);
		DEFINE_MEMBER_N(Vector3 EndPosition, 0x24);
		DEFINE_MEMBER_N(Vector3 CursorPosition, 0x24 + sizeof(Vector3));
		DEFINE_MEMBER_N(Vector3 UnknownPosition, 0x24 + sizeof(Vector3) * 2);
	};

	void ShowDebugMessage() const
	{
		Logger::Warn("CasterHandle: %i", this->CasterHandle);
		Logger::Warn("TargetHandle: %i", this->TargetHandle);
		Logger::Warn("StartPosition :(%f, %f, %f)", this->StartPosition.x, this->StartPosition.y, this->StartPosition.z);
		Logger::Warn("EndPosition: (%f, %f, %f)", this->EndPosition.x, this->EndPosition.y, this->EndPosition.z);
		Logger::Warn("CursorPosition: (%f, %f, %f)", this->CursorPosition.x, this->CursorPosition.y, this->CursorPosition.z);
		Logger::Warn("UnknownPosition: (%f, %f, %f)", this->UnknownPosition.x, this->UnknownPosition.y, this->UnknownPosition.z);
	}
};
