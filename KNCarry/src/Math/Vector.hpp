#pragma once

#define M_PI 3.14159265358979323846f
#define TO_RADIAN( degree ) (( degree ) * (M_PI / 180.f))
#define TO_DEGREE( radian ) (( radian ) * (180.f / M_PI))

struct Vector3 {
	float x, y, z;
	Vector3() = default;
	constexpr Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	constexpr Vector3(const float x, const float z) : x(x), y(0.0f), z(z) {}

	[[nodiscard]] bool IsValid() const;
	[[nodiscard]] float GetLengthSqrt() const;
	[[nodiscard]] float GetLength() const;
	[[nodiscard]] float GetDistanceSqrt(const Vector3& other) const;
	[[nodiscard]] float GetDistance(const Vector3& other) const;
	[[nodiscard]] Vector3 PerpendicularClockwise() const;
	[[nodiscard]] Vector3 PerpendicularCounterClockwise() const;
	[[nodiscard]] Vector3 GetNormalized() const;
	[[nodiscard]] Vector3 GetRotated(float angle) const;
	[[nodiscard]] float GetAngleBetween(const Vector3& other) const;
	[[nodiscard]] float DotProduct(const Vector3& other) const;
	[[nodiscard]] float CrossProduct(const Vector3& other) const;
	[[nodiscard]] Vector3 Extend(const Vector3& to, float distance) const;
	[[nodiscard]] bool IsOnScreen(float threshold = 0.f) const;

	Vector3& operator += (const Vector3& other);
	Vector3& operator -= (const Vector3& other);
	Vector3& operator *= (float value);
	Vector3& operator /= (float value);
	Vector3 operator + () const;
	Vector3 operator - () const;
	Vector3 operator + (const Vector3& other) const;
	Vector3 operator - (const Vector3& other) const;
	Vector3 operator * (float value) const;
	Vector3 operator / (float value) const;
	bool operator == (const Vector3& other) const;
	bool operator != (const Vector3& other) const;
};

struct Vector2 {
public:

	float x, y;

public:

	Vector2() = default;
	constexpr Vector2(float flX, float flY) : x(flX), y(flY) {};
	constexpr Vector2(const Vector3& stVector3) : x(stVector3.x), y(stVector3.y) {};
};