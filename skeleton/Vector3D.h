#pragma once

#include <PxPhysics.h>
#include <cmath>

class Vector3D
{
public:

	// ------ Constructors ------

	Vector3D() noexcept :
		x(0),
		y(0),
		z(0)
	{}

	Vector3D(float _x, float _y, float _z) noexcept :
		x(_x),
		y(_y),
		z(_z)
	{ }

	Vector3D(const physx::PxVec3& pxVec) noexcept :
		x(pxVec.x),
		y(pxVec.y),
		z(pxVec.z)
	{ }

	// ------ Functions ------

	float magnitude() const;

	Vector3D normalized() const;

	float dot(const Vector3D& v) const;

	Vector3D cross(const Vector3D& v) const;

	// ------ Attributes ------

	float x, y, z;

	// ------ Operators ------

	Vector3D& operator=(const physx::PxVec3& pxVec) noexcept {
		x = pxVec.x; y = pxVec.y; z = pxVec.z;
		return *this;
	}

	Vector3D operator+(const Vector3D& vec) const noexcept {
		return Vector3D(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector3D operator-(const Vector3D& vec) const noexcept {
		return Vector3D(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector3D operator*(float scalar) const noexcept {
		return Vector3D(x * scalar, y * scalar, z * scalar);
	}

	Vector3D operator/(float scalar) const noexcept {
		return Vector3D(x / scalar, y / scalar, z / scalar);
	}

	Vector3D& operator+=(const Vector3D& vec) noexcept {
		x += vec.x; y += vec.y; z += vec.z;
		return *this;
	}

	Vector3D& operator-=(const Vector3D& vec) noexcept {
		x -= vec.x; y -= vec.y; z -= vec.z;
		return *this;
	}

	Vector3D& operator/=(float scalar) noexcept {
		x /= scalar; y /= scalar; z /= scalar;
		return *this;
	}

	bool operator==(const Vector3D& other) const noexcept {
		constexpr float eps = 1e-5f;
		return std::abs(x - other.x) < eps &&
			std::abs(y - other.y) < eps &&
			std::abs(z - other.z) < eps;
	}

	operator physx::PxVec3() const noexcept {
		return physx::PxVec3(x, y, z);
	}
};

