#include "./Vector.hpp"
#include "../Game/R3DRenderer/R3DRenderer.hpp"

bool Vector3::IsValid() const {
	return this->x != 0.f && this->z != 0.f;
}

float Vector3::GetLengthSqrt() const {
	return this->x * this->x + this->z * this->z;
}

float Vector3::GetLength() const {
	return sqrtf(this->x * this->x + this->z * this->z);
}

float Vector3::GetDistanceSqrt(const Vector3& other) const {
	const float flDeltaX = this->x - other.x;
	const float flDeltaZ = this->z - other.z;
	return flDeltaX * flDeltaX + flDeltaZ * flDeltaZ;
}

float Vector3::GetDistance(const Vector3& other) const {
	return sqrtf(this->GetDistanceSqrt(other));
}

Vector3 Vector3::PerpendicularClockwise() const {
	return {-this->z, this->y, this->x};
}

Vector3 Vector3::PerpendicularCounterClockwise() const {
	return {this->z, this->y, -this->x};
}

Vector3 Vector3::GetNormalized() const
{
	const float length = this->GetLength();
	if (length == 0.f)
		return *this;

	const float inverse = 1.0f / length;
	return { this->x * inverse, 0.f, this->z * inverse };
}

Vector3 Vector3::GetRotated(const float angle) const {
	const float flCos = cosf(angle);
	const float flSin = sinf(angle);

	Vector3 vecResult = *this;
	vecResult.x = this->x * flCos - this->z * flSin;
	vecResult.z = this->z * flCos + this->x * flSin;
	return vecResult;
}

float Vector3::GetAngleBetween(const Vector3& other) const {
	return acosf(this->DotProduct(other));
}

float Vector3::DotProduct(const Vector3& other) const {
	return this->x * other.x + this->z * other.z;
}

float Vector3::CrossProduct(const Vector3& other) const {
	return this->x * other.z - this->z * other.x;
}

Vector3 Vector3::Extend(const Vector3& to, const float distance) const
{
	return *this + (to - *this).GetNormalized() * distance;
}

bool Vector3::IsOnScreen(const float threshold) const {
	return this->x > -threshold && this->y > -threshold && this->x < float(R3DRenderer::GetScreenWidth()) + threshold && this->y < float(R3DRenderer::GetScreenHeight()) + threshold;
}

Vector3& Vector3::operator += (const Vector3& other) {
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Vector3& Vector3::operator -= (const Vector3& other) {
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

Vector3& Vector3::operator *= (const float value) {
	this->x *= value;
	this->y *= value;
	this->z *= value;
	return *this;
}

Vector3& Vector3::operator /= (const float value) {
	const float flInverse = 1.f / value;
	this->x *= flInverse;
	this->y *= flInverse;
	this->z *= flInverse;
	return *this;
}

Vector3 Vector3::operator + () const {
	return *this;
}

Vector3 Vector3::operator - () const {
	return { -this->x, -this->y, -this->z };
}

Vector3 Vector3::operator + (const Vector3& other) const {
	return { this->x + other.x, this->y + other.y, this->z + other.z };
}

Vector3 Vector3::operator - (const Vector3& other) const {
	return { this->x - other.x, this->y - other.y, this->z - other.z };
}

Vector3 Vector3::operator * (const float value) const {
	return { this->x * value, this->y * value, this->z * value };
}

Vector3 Vector3::operator / (const float value) const {
	const float flInverse = 1.f / value;
	return { this->x * flInverse, this->y * flInverse, this->z * flInverse };
}

bool Vector3::operator == (const Vector3& other) const {
	return this->x == other.x && this->y == other.y && this->z == other.z;
}

bool Vector3::operator != (const Vector3& other) const {
	return this->x != other.x || this->y != other.y || this->z != other.z;
}
