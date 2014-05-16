/*
 * MatrixTransform.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: tyler
 */

#include "MatrixTransform.h"
#include "VectorOperations.h"
#include "Quaternion.h"
#include "QuaternionOperations.h"

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

/**
 * @brief Creates a frustrum projection matrix
 *
 * @param left left x Coordinate at near clipping plane
 * @param right right x Coordinate at near clipping plane
 * @param bottom bottom y Coordinate at near clipping plane
 * @param top top y Coordinate at near clipping plane
 * @param near z Coordinate of near clipping plane
 * @param far z Coordinate of far clipping plane
 * @return mat4 for projecting vertices into a frustrum
 */
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
	return translate(vec3(x, y, z));
}

mat4 translate(vec3 translateVector) {
	mat4 result(1.f);

	result[3][0] = translateVector.x;
	result[3][1] = translateVector.y;
	result[3][2] = translateVector.z;

	return result;
}

mat4 scale(float x, float y, float z) {
	return scale(vec3(x, y, z));
}

mat4 lookAt(vec3 cameraPosition, vec3 lookCenter, vec3 up) {
	vec3 front = normalize(lookCenter - cameraPosition);
	vec3 right = normalize(cross(front, up));
	up = cross(right, front);

	mat4 result(1);
	result[0][0] = right.x;
	result[1][0] = right.y;
	result[2][0] = right.z;
	result[0][1] = up.x;
	result[1][1] = up.y;
	result[2][1] = up.z;
	result[0][2] = -front.x;
	result[1][2] = -front.y;
	result[2][2] = -front.z;
	result[3][0] = -dot(right, cameraPosition);
	result[3][1] = -dot(up, cameraPosition);
	result[3][2] = dot(front, cameraPosition);
	return result;
}

mat4 lookAt(vec3 cameraPosition, float yaw, float pitch, float roll) {
	ts::Vector::quat rotation = ts::Vector::angleAxisToQuaternion(-roll, 0, 0, 1) * ts::Vector::angleAxisToQuaternion(-pitch, 1, 0, 0) * ts::Vector::angleAxisToQuaternion(yaw, 0, 1, 0);
	return ts::Vector::quaternionToMatrix(rotation) * translate(-cameraPosition);
}

mat4 scale(vec3 scaleVector) {
	mat4 result(1.f);

	result[0][0] = scaleVector.x;
	result[1][1] = scaleVector.y;
	result[2][2] = scaleVector.z;

	return result;
}

}/* namespace Vector */
} /* namespace ts */
