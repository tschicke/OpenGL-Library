/*
 * QuaternionOperations.h
 *
 *  Created on: Apr 26, 2014
 *      Author: tyler
 */

#ifndef QUATERNIONOPERATIONS_H_
#define QUATERNIONOPERATIONS_H_

#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"

namespace ts {
namespace Vector {

float norm(quat quaternion);
quat normalize(quat quaternion);

quat conjugate(quat quaternion);

quat inverse(quat quaternion);

void getQuaternionDirection(quat quaternion, vec3& front, vec3& right, vec3& up);

mat4 quaternionToMatrix(quat quaternion);

quat angleAxisToQuaternion(float angle, vec3 axis);
quat angleAxisToQuaternion(float angle, float axisX, float axisY, float axisZ);

quat angleBetweenVectors(vec3 v1, vec3 v2);

} /* namespace Vector */
} /* namespace ts */
#endif /* QUATERNIONOPERATIONS_H_ */
