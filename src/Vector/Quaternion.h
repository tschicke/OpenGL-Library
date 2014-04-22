/*
 * Quaternion.h
 *
 *  Created on: Apr 21, 2014
 *      Author: Tyler
 */

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <cstddef>

namespace ts {
namespace Vector {

class Quaternion {
public:
	Quaternion();

	union {
		int a, w;
	};
	union {
		int b, x;
	};
	union {
		int c, y;
	};
	union {
		int d, z;
	};

	float& operator[](std::size_t index);
	const float& operator[](std::size_t index) const;

	Quaternion& operator*=(const Quaternion& quaternion);
};

Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

} /* namespace Vector */
} /* namespace ts */
#endif /* QUATERNION_H_ */
