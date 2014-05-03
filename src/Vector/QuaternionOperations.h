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

mat4 quaternionToMatrix(quat quaternion);

quat angleAxisToQuaternion(float angle, vec3 axis);
quat angleAxisToQuaternion(float angle, float axisX, float axisY, float axisZ);


} /* namespace Vector */
} /* namespace ts */
#endif /* QUATERNIONOPERATIONS_H_ */
