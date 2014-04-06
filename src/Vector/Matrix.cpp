/*
 * Matrix.cpp
 *
 *  Created on: Apr 5, 2014
 *      Author: tyler
 */

#include <assert.h>

#include "Matrix.h"

namespace ts {
namespace Vector {

Matrix4::Matrix4() {
	columns[0] = vec4(1, 0, 0, 0);
	columns[1] = vec4(0, 1, 0, 0);
	columns[2] = vec4(0, 0, 1, 0);
	columns[3] = vec4(0, 0, 0, 1);
}

Matrix4::Matrix4(vec4 column0, vec4 column1, vec4 column2, vec4 column3) {
	columns[0] = column0;
	columns[1] = column1;
	columns[2] = column2;
	columns[3] = column3;
}

vec4& Matrix4::operator[](std::size_t index) {
	assert(index < 4);
	return columns[index];
}

const vec4& Matrix4::operator [](std::size_t index) const {
	assert(index < 4);
	return const_cast<Matrix4&>(*this)[index];
}

Matrix4& Matrix4::operator+=(const Matrix4& matrix) {
	columns[0] += matrix.columns[0];
	columns[1] += matrix.columns[1];
	columns[2] += matrix.columns[2];
	columns[3] += matrix.columns[3];
	return *this;
}

Matrix4& Matrix4::operator -=(const Matrix4& matrix) {
	columns[0] -= matrix.columns[0];
	columns[1] -= matrix.columns[1];
	columns[2] -= matrix.columns[2];
	columns[3] -= matrix.columns[3];
	return *this;
}

Matrix4& Matrix4::operator *=(const Matrix4& matrix) {
	return (*this = *this * matrix);
}

Matrix4& Matrix4::operator *=(const float scalar) {
	columns[0] *= scalar;
	columns[1] *= scalar;
	columns[2] *= scalar;
	columns[3] *= scalar;
	return *this;
}

} /* namespace Vector */
} /* namespace ts */

ts::Vector::Matrix4 ts::Vector::operator +(const Matrix4& matrix1, const Matrix4& matrix2) {
	return Matrix4(matrix1) += matrix2;
}

ts::Vector::Matrix4 ts::Vector::operator -(const Matrix4& matrix1, const Matrix4& matrix2) {
	return Matrix4(matrix1) -= matrix2;
}

ts::Vector::Matrix4 ts::Vector::operator *(const Matrix4& matrix1, const Matrix4& matrix2) {
	Matrix4 result;
	result[0] = matrix1 * matrix2[0];
	result[1] = matrix1 * matrix2[1];
	result[2] = matrix1 * matrix2[2];
	result[3] = matrix1 * matrix2[3];
	return result;
}

ts::Vector::Matrix4 ts::Vector::operator *(const Matrix4& matrix, const float scalar) {
	return Matrix4(matrix) *= scalar;
}

ts::Vector::Matrix4 ts::Vector::operator *(const float scalar, const Matrix4& matrix) {
	return Matrix4(matrix) *= scalar;
}

ts::Vector::Vector4 ts::Vector::operator *(const Matrix4& matrix, const Vector4& vector) {
	return vector[0] * matrix[0] + vector[1] * matrix[1] + vector[2] * matrix[2] + vector[3] * matrix[3];
}
