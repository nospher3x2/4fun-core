#pragma once
#pragma once
#include <corecrt_math.h>

#define M_PI 3.14159265358979323846f

struct Vector2
{
	float x;
	float y;

	Vector2() = default;
	Vector2(float x, float y) : x(x), y(y) {}
};

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3() = default;
	Vector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

	auto operator-(const Vector3& v) const -> Vector3
	{
		return { this->x - v.x, this->y - v.y, this->z - v.z };
	}

	auto operator-(const float mod) const->Vector3\
	{
		return { this->x - mod, this->y - mod, this->z - mod };
	}

	auto operator+(const Vector3& v) const -> Vector3
	{
		return { this->x + v.x, this->y + v.y, this->z + v.z };
	}

	auto operator+(const float mod) const -> Vector3
	{
		return { this->x + mod, this->y + mod, this->z + mod };
	}

	auto operator/(const Vector3& v) const -> Vector3
	{
		return { this->x / v.x, this->y / v.y, this->z / v.z };
	}

	auto operator/(const float mod) const -> Vector3
	{
		return { this->x / mod, this->y / mod, this->z / mod };
	}

	auto operator*(const Vector3& v) const -> Vector3
	{
		return { this->x * v.x, this->y * v.y, this->z * v.z };
	}

	auto operator*(const float mod) const -> Vector3
	{
		return { this->x * mod, this->y * mod, this->z * mod };
	}

	auto Perpendicular() const -> Vector3
	{
		return { -z,y,x };
	}

	auto Length() const -> float
	{
		return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	auto Normalized() const -> Vector3
	{
		if (auto const length = this->Length(); length != 0)
		{
			auto const inv = 1.0f / length;
			return { this->x * inv, this->y * inv, this->z * inv };
		}

		return *this;
	}

	auto mag_sq() const -> float
	{
		return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
	}

	auto mag() const -> float
	{
		return sqrtf(this->mag_sq());
	}

	auto dist_sq(const Vector3& v) const -> float
	{
		return (*this - v).mag_sq();
	}

	auto dist(const Vector3& v) const -> float
	{
		return (*this - v).mag();
	}
};

struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};