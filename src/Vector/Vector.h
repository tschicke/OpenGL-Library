/*
 * Vector.h
 *
 *  Created on: Apr 2, 2014
 *      Author: tyler
 */

#ifndef VECTOR_H_
#define VECTOR_H_

namespace ts {
namespace Vector{

class Vector2 {
	Vector2();
	Vector2(float x, float y);

	union {
		float x, u;
	};
	union {
		float y, v;
	};
};

class Vector3 {
public:
	Vector3();
	Vector3(float x, float y, float z);

	union {
		float x, r, u;
	};
	union {
		float y, g, v;
	};
	union {
		float z, b, w;
	};

	float& operator[](std::size_t index);
	const float& operator[](std::size_t index) const;

};

typedef Vector3 vec3;

} /* namespace Vector */
} /* namespace ts */
#endif /* VECTOR_H_ */
