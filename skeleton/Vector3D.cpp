#include "Vector3D.h"

float 
Vector3D::magnitude() const { // |A| = sqrt(A * A)
	return std::sqrt(x * x + y * y + z * z);
}

Vector3D 
Vector3D::normalized() const { // A / |A|
	const float mag = magnitude();
	if (mag > 0.0f) {
		return *this / mag;
	}
	return Vector3D(0.0f, 0.0f, 0.0f);
}

float 
Vector3D::dot(const Vector3D& v) const { // A * B = (Ax * Bx) + (Ay * By) + (Az * Bz)
	return x * v.x + y * v.y + z * v.z;
}

Vector3D 
Vector3D::cross(const Vector3D& v) const {
	return Vector3D(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}