/*
 * Quaternion.cpp
 *
 *  Created on: Apr 21, 2014
 *      Author: Tyler
 */

#include "Quaternion.h"

#include <assert.h>

#include <iostream>

namespace ts {
namespace Vector {

Quaternion::Quaternion() {
	a = b = c = d = 0;
}

Quaternion::Quaternion(float a, float b, float c, float d) {
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
}

Quaternion::Quaternion(float a, vec3 vector) {
	this->a = a;
	this->b = vector.x;
	this->c = vector.y;
	this->d = vector.z;
}

Quaternion& Quaternion::operator/=(const float scalar) {
	a /= scalar;
	b /= scalar;
	c /= scalar;
	d /= scalar;

	return *this;
}

float& Quaternion::operator [](std::size_t index) {
	assert(index < 4);
	return (&x)[index];
}

const float& Quaternion::operator [](std::size_t index) const {
	return const_cast<Quaternion&>(*this)[index];
}

Quaternion operator *(const Quaternion& q1, const Quaternion& q2) {
	Quaternion result;

	result.a = q1.a * q2.a - q1.b * q2.b - q1.c * q2.c - q1.d * q2.d;
	result.b = q1.a * q2.b + q1.b * q2.a + q1.c * q2.d - q1.d * q2.c;
	result.c = q1.a * q2.c - q1.b * q2.d + q1.c * q2.a + q1.d * q2.b;
	result.d = q1.a * q2.d + q1.b * q2.c - q1.c * q2.b + q1.d * q2.a;

	return result;
}

Quaternion operator /(const Quaternion& q, const float s) {
	return Quaternion(q) /= s;
}

Vector3 Quaternion::getAxis(){
	return vec3(x, y, z);
}

void Quaternion::print() {
	std::cout << "(" << a << ", " << b << "i, " << c << "j, " << d << "k)\n";
}

} /* namespace Vector */
} /* namespace ts */
