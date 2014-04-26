/*
 * Quaternion.cpp
 *
 *  Created on: Apr 21, 2014
 *      Author: Tyler
 */

#include "Quaternion.h"

#include <assert.h>

namespace ts {
namespace Vector {

Quaternion::Quaternion() {
	a = b = c = d = 0;
}

float& Quaternion::operator [](std::size_t index) {
	assert(index < 4);
	return (&x)[index];
}

const float& Quaternion::operator [](std::size_t index) const {
	return const_cast<Quaternion&>(*this)[index];
}

Quaternion& Quaternion::operator *=(const Quaternion& q) {
	float an = a * q.a - b * q.b - c * q.c - d * q.d;
	float bn = a * q.b + b * q.a + c * q.d - d * q.c;
	float cn = a * q.c - b * q.d + c * q.a + d * q.b;
	float dn = a * q.d + b * q.c - c * q.b + d * q.a;

	a = an;
	b = bn;
	c = cn;
	d = dn;

	return *this;
}

Quaternion operator *(const Quaternion& q1, const Quaternion& q2) {
	return Quaternion(q1) *= q2;
}

} /* namespace Vector */
} /* namespace ts */
