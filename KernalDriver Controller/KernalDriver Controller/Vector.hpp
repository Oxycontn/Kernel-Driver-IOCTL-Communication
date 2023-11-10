#pragma once

#include <numbers>
#include <cmath>

#include "Global.hpp"

struct view_matrix_t
{
	float* operator[](int index)
	{
		return matrix[index];
	}

	float matrix[4][4];
};

struct Vector3
{
	constexpr Vector3(
		const float x = 0.f,
		const float y = 0.f,
		const float z = 0.f)noexcept :
		x(x), y(y), z(z) {}

	constexpr const Vector3& operator-(const Vector3& other) const noexcept
	{
		return Vector3{ x - other.x, y - other.y, z - other.z };
	}

	constexpr const Vector3& operator+(const Vector3& other) const noexcept
	{
		return Vector3{ x + other.x, y + other.y, z + other.z };
	}

	constexpr const Vector3& operator/(const float factor) const noexcept
	{
		return Vector3{ x / factor, y / factor, z / factor };
	}

	constexpr const Vector3& operator*(const float factor) const noexcept
	{
		return Vector3{ x * factor, y * factor, z * factor };
	}

	Vector3 WorldtoScreen(view_matrix_t matrix) const
	{
		float _x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3];
		float _y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3];
		float w = matrix[3][0] * x + matrix[3][1] * y + matrix[3][2] * z + matrix[3][3];

		if (w < 0.001f)
			return 0;

		float inv_w = 1.f / w;
		_x *= inv_w;
		_y *= inv_w;

		float screen_x = screenWidth * 0.5f;
		float screen_y = screenHeight * 0.5f;

		screen_x += 0.5f * _x * screenWidth + 0.5f;
		screen_y -= 0.5f * _y * screenHeight + 0.5f;

		return { screen_x,screen_y,w };
	}

	float x, y, z;
};