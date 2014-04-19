/*
 * MatrixTransform.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: tyler
 */

#include "MatrixTransform.h"

#include <cmath>

namespace ts {
namespace Vector {

mat4 ortho(float left, float right, float bottom, float top, float near, float far) {
	mat4 result(1);

	result[0][0] = 2 / (right - left);
	result[3][0] = -(right + left) / (right - left);
	result[1][1] = 2 / (top - bottom);
	result[3][1] = -(top + bottom) / (top - bottom);
	result[2][2] = 2 / (far - near);
	result[3][2] = -(far + near) / (far - near);

	return result;

}

mat4 frustrum(float left, float right, float bottom, float top, float near, float far) {
	mat4 result(0);

	result[0][0] = 2 * near / (right - left);
	result[2][0] = (right + left) / (right - left);
	result[1][1] = 2 * near / (top - bottom);
	result[2][1] = (top + bottom) / (top - bottom);
	result[2][2] = -(far + near) / (far - near);
	result[3][2] = -2 * far * near / (far - near);
	result[2][3] = -1;

	return result;
}

mat4 perspective(float fov, float width, float height, float near, float far) {
	mat4 result(0);

	float rad = fov * 3.14159265358979f / 180;
	float tanHalfFOV = tan(rad / 2);

	result[0][0] = 1 / tanHalfFOV;
	result[1][1] = width / (height * tanHalfFOV);
	result[2][2] = -(far + near) / (far - near);
	result[3][2] = -2 * far * near / (far - near);
	result[2][3] = -1;

	return result;
}

mat4 translate(float x, float y, float z) {
	mat4 result(1.f);

	result[3][0] = x;
	result[3][1] = y;
	result[3][2] = z;

	return result;
}

mat4 scale(float x, float y, float z) {
	mat4 result(1.f);

	result[0][0] = x;
	result[1][1] = y;
	result[2][2] = z;

	return result;
}

}/* namespace Vector */
} /* namespace ts */
