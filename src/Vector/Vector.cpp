/*
 * Vector.cpp
 *
 *  Created on: Apr 2, 2014
 *      Author: tyler
 */

#include "Vector.h"

#include <assert.h>

#include <iostream>

namespace ts {
namespace Vector {

Vector2::Vector2() {
	x = y = 0;
}

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

/*
 * Vector3 Function declarations
 */

Vector3::Vector3() {
	x = y = z = 0;
}

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float& Vector3::operator[](std::size_t index) {
	assert(index < 3);
	return (&x)[index];
}

const float& Vector3::operator[](std::size_t index) const {
	assert(index < 3);
	return const_cast<Vector3&>(*this)[index];
}

Vector3& Vector3::operator +=(const Vector3& v1) {
	x += v1.x;
	y += v1.y;
	z += v1.z;
	return *this;
}

Vector3& Vector3::operator -=(const Vector3& v1) {
	x -= v1.x;
	y -= v1.y;
	z -= v1.z;
	return *this;
}

Vector3 Vector3::operator -(){
	return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator *=(const float scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vector3& Vector3::operator /=(const float scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

Vector3 operator *(const Vector3& v1, const float scalar) {
	return Vector3(v1) *= scalar;
}

Vector3 operator *(const float scalar, const Vector3& v1) {
	return Vector3(v1) *= scalar;
}

Vector3 operator /(const Vector3& v1, const float scalar) {
	return Vector3(v1) /= scalar;
}

Vector3 operator /(const float scalar, const Vector3& v1) {
	return Vector3(v1) /= scalar;
}

void Vector3::print(){
	std::cout << "(" << x << ", " << y << ", " << z << ")\n";
}

/*
 * Vector4 Function declarations
 */

Vector4::Vector4() {
	x = y = z = w = 0;
}

Vector4::Vector4(Vector3 vec, float w) {
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = w;
}

Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector3 Vector4::xyz(){
	return vec3(x, y, z);
}

float& Vector4::operator [](std::size_t index) {
	assert(index < 4);
	return (&x)[index];
}

const float& Vector4::operator [](std::size_t index) const {
	assert(index < 4);
	return const_cast<Vector4&>(*this)[index];
}

Vector4& Vector4::operator +=(const Vector4& v1) {
	x += v1.x;
	y += v1.y;
	z += v1.z;
	w += v1.w;
	return *this;
}

Vector4& Vector4::operator -=(const Vector4& v1) {
	x -= v1.x;
	y -= v1.y;
	z -= v1.z;
	w -= v1.w;
	return *this;
}

Vector4 Vector4::operator -(){
	return Vector4(-x, -y, -z, -w);
}

Vector4& Vector4::operator *=(const float scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

Vector4& Vector4::operator /=(const float scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

Vector4 operator *(const Vector4& v1, const float scalar) {
	return Vector4(v1) *= scalar;
}

Vector4 operator *(const float scalar, const Vector4& v1) {
	return Vector4(v1) *= scalar;
}

Vector4 operator /(const Vector4& v1, const float scalar) {
	return Vector4(v1) /= scalar;
}

Vector4 operator /(const float scalar, const Vector4& v1) {
	return Vector4(v1) /= scalar;
}

//Vector2 operator +(const Vector2& v1, const Vector2& v2) {
//	return Vector2(v1) += v2;
//}
//
//Vector2 operator -(const Vector2& v1, const Vector2& v2) {
//	return Vector2(v1) -= v2;
//}

Vector3 operator +(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1) += v2;
}

Vector3 operator -(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1) -= v2;
}

Vector4 operator +(const Vector4& v1, const Vector4& v2) {
	return Vector4(v1) += v2;
}

Vector4 operator -(const Vector4& v1, const Vector4& v2) {
	return Vector4(v1) -= v2;
}

void Vector4::print(){
	std::cout << "(" << x << ", " << y << ", " << z << ", " << w << ")\n";
}

} /* namespace Vector */
} /* namespace ts */


