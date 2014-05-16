/*
 * Vector.h
 *
 *  Created on: Apr 2, 2014
 *      Author: tyler
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstddef>

namespace ts {
namespace Vector {

class Vector2 {
public:
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
		float z, b, s;
	};

	float& operator[](std::size_t index);
	const float& operator[](std::size_t index) const;

	Vector3& operator+=(const Vector3& v1);
	Vector3& operator-=(const Vector3& v1);

	Vector3 operator-();

	Vector3& operator*=(const float scalar);
	Vector3& operator/=(const float scalar);

	void print();
};

class Vector4 {
public:
	Vector4();
	Vector4(Vector3 vec, float w);
	Vector4(float x, float y, float z, float w);

	union {
		float x, r, u;
	};
	union {
		float y, g, v;
	};
	union {
		float z, b, s;
	};
	union {
		float w, a, t;
	};

	float& operator[](std::size_t index);
	const float& operator[](std::size_t index) const;

	Vector4& operator+=(const Vector4& v1);
	Vector4& operator-=(const Vector4& v1);

	Vector4 operator-();

	Vector4& operator*=(const float scalar);
	Vector4& operator/=(const float scalar);

	void print();
};

//Vector2 operator+(const Vector2& v1, const Vector2& v2);
//Vector2 operator-(const Vector2& v1, const Vector2& v2);

Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(const Vector3& v1, const float scalar);
Vector3 operator*(const float scalar, const Vector3& v1);
Vector3 operator/(const Vector3& v1, const float scalar);
Vector3 operator/(const float scalar, const Vector3& v1);

Vector4 operator+(const Vector4& v1, const Vector4& v2);
Vector4 operator-(const Vector4& v1, const Vector4& v2);
Vector4 operator*(const Vector4& v1, const float scalar);
Vector4 operator*(const float scalar, const Vector4& v1);
Vector4 operator/(const Vector4& v1, const float scalar);
Vector4 operator/(const float scalar, const Vector4& v1);

typedef Vector2 vec2;
typedef Vector3 vec3;
typedef Vector4 vec4;

} /* namespace Vector */
} /* namespace ts */
#endif /* VECTOR_H_ */
