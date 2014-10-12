/*
 * Quaternion.h
 *
 *  Created on: Apr 21, 2014
 *      Author: Tyler
 */

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <cstddef>

#include "Vector.h"

namespace ts {
namespace Vector {

class Quaternion {
public:
	Quaternion();
	Quaternion(float a, float b, float c, float d);
	Quaternion(float a, vec3 vector);

	union {
		float a, w;
	};
	union {
		float b, x;
	};
	union {
		float c, y;
	};
	union {
		float d, z;
	};

	Vector3 getAxis();

	void print();

	Quaternion& operator/=(const float scalar);

	bool operator == (const Quaternion& quaternion) const;

	float& operator[](std::size_t index);
	const float& operator[](std::size_t index) const;
};

Quaternion operator*(const Quaternion& q1, const Quaternion& q2);
Quaternion operator/(const Quaternion& quaternion, const float scalar);

typedef Quaternion quat;

} /* namespace Vector */
} /* namespace ts */
#endif /* QUATERNION_H_ */
