#pragma once
#include "../../../Patchables/Offsets.hpp"
#include "../../../Math/Vector.hpp"
#include <vector>

class PathControllerCommon
{
public:
	CLASS_GETTER(Vector3, GetTargetPosition, 0x14)
	CLASS_GETTER(float, GetMovementSpeed, 0x2B8)
	CLASS_GETTER(bool, IsMoving, 0x2BC)
	CLASS_GETTER(Vector3, GetStartPosition, 0x2D0)
	CLASS_GETTER(Vector3, GetEndPosition, 0x2DC)
	CLASS_GETTER(uint8_t, GetCurrentWaypointIndex, 0x2C0)
	CLASS_GETTER(std::vector<Vector3>, GetWaypoints, 0x2E8)
	CLASS_GETTER(size_t, GetCurrentWaypointsSize, 0x2F0)
	CLASS_GETTER(bool, IsDashing, 0x324)
	CLASS_GETTER(float, GetDashSpeed, 0x300)
	CLASS_GETTER(Vector3, GetServerPosition, 0x414)
};

