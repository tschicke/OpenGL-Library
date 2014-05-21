/*
 * QuaternionOperations.cpp
 *
 *  Created on: Apr 26, 2014
 *      Author: tyler
 */

#include "QuaternionOperations.h"
#include "VectorOperations.h"

#include <iostream>

#include <cmath>

namespace ts {
namespace Vector {

float norm(quat q) {
	return sqrt(q.a * q.a + q.b * q.b + q.c * q.c + q.d * q.d);
}

quat normalize(quat q) {
	return q / norm(q);
}

void getQuaternionDirection(quat q, vec3& front, vec3& right, vec3& up) {
	vec3 vq = q.getAxis();
	front = vec3(0, 0, -1);
	right = vec3(1, 0, 0);
	up = vec3(0, 1, 0);
	front = front + cross(2 * vq, cross(vq, front) + q.w * front);
	right = right + cross(2 * vq, cross(vq, right) + q.w * right);
	up = cross(right, front);
}

mat4 quaternionToMatrix(quat q) {
	mat4 result(1.f);

	q = normalize(q);

	result[0][0] = 1 - 2 * (q.y * q.y + q.z * q.z);
	result[1][0] = 2 * (q.x * q.y - q.z * q.w);
	result[2][0] = 2 * (q.x * q.z + q.y * q.w);

	result[0][1] = 2 * (q.x * q.y + q.z * q.w);
	result[1][1] = 1 - 2 * (q.x * q.x + q.z * q.z);
	result[2][1] = 2 * (q.y * q.z - q.x * q.w);

	result[0][2] = 2 * (q.x * q.z - q.y * q.w);
	result[1][2] = 2 * (q.y * q.z + q.x * q.w);
	result[2][2] = 1 - 2 * (q.x * q.x + q.y * q.y);

	return result;
}

quat angleAxisToQuaternion(float angle, vec3 axis) {
	angle = angle * 3.14159265358979f / 180.f;
	axis = normalize(axis);
	return quat(cos(angle / 2), sin(angle / 2) * axis);
}

quat angleAxisToQuaternion(float angle, float axisX, float axisY, float axisZ) {
	return angleAxisToQuaternion(angle, vec3(axisX, axisY, axisZ));
}

} /* namespace Vector */
} /* namespace ts */
