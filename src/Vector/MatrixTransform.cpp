/*
 * MatrixTransform.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: tyler
 */

#include "MatrixTransform.h"

namespace ts {
namespace Vector {

mat4 ortho(float left, float right, float bottom, float top, float near, float far) {
	mat4 result(1);

	result[0][0] = 2 / (right - left);
	result[3][0] = -(right + left) / (right - left);
	result[1][1] = 2 / (top - bottom);
	result[3][1] = -(top + bottom) / (top - bottom);
	result[2][2] = -2 / (far - near);
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

mat4 perspective(float fov, float width, float height, float near, float far){
}

}/* namespace Vector */
} /* namespace ts */
