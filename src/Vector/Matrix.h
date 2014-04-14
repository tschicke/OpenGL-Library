/*
 * Matrix.h
 *
 *  Created on: Apr 5, 2014
 *      Author: tyler
 */

#ifndef MATRIX4_H_
#define MATRIX4_H_

#include "Vector.h"

namespace ts {
namespace Vector {

class Matrix4 {
public:
	Matrix4();
	Matrix4(float diagonals);
	Matrix4(vec4 column0, vec4 column1, vec4 column2, vec4 column3);

	vec4 columns[4];

	vec4& operator[](std::size_t index);
	const vec4& operator[](std::size_t index) const;

	Matrix4& operator+=(const Matrix4& matrix);
	Matrix4& operator-=(const Matrix4& matrix);
	Matrix4& operator*=(const Matrix4& matrix);
	Matrix4& operator*=(const float scalar);
};

Matrix4 operator+(const Matrix4& matrix1, const Matrix4& matrix2);
Matrix4 operator-(const Matrix4& matrix1, const Matrix4& matrix2);
Matrix4 operator*(const Matrix4& matrix1, const Matrix4& matrix2);
Matrix4 operator*(const Matrix4& matrix, const float scalar);
Matrix4 operator*(const float scalar, const Matrix4& matrix);
Vector4 operator*(const Matrix4& matrix, const Vector4& vector);

typedef Matrix4 mat4;

} /* namespace Vector */
} /* namespace ts */
#endif /* MATRIX4_H_ */
