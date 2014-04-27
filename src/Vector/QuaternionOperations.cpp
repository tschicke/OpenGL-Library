/*
 * QuaternionOperations.cpp
 *
 *  Created on: Apr 26, 2014
 *      Author: tyler
 */

#include "QuaternionOperations.h"

#include <cmath>

namespace ts {
namespace Vector {

float norm(quat quaternion){

}

mat4 ts::Vector::quaternionToMatrix(quat q) {
	mat4 result(1.f);

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

quat ts::Vector::quatFromAngleAxis(float angle, vec3 axis) {
	return quat(cos(angle / 2), sin(angle / 2) * axis);
}

quat ts::Vector::quatFromAngleAxis(float angle, float axisX, float axisY, float axisZ) {
	return quatFromAngleAxis(angle, vec3(axisX, axisY, axisZ));
}

} /* namespace Vector */
} /* namespace ts */
