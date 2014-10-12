/*
 * Interpolation.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: Tyler
 */

#include <assert.h>

#include "Interpolation.h"
#include "../Vector/Quaternion.h"
#include "../Vector/QuaternionOperations.h"

namespace ts {

Vector::quat interpolateQuatLinear(Vector::quat q1, Vector::quat q2, float x) {
	Vector::quat returnQuat;
	returnQuat.w = q1.w * (1 - x) + q2.w * x;
	returnQuat.x = q1.x * (1 - x) + q2.x * x;
	returnQuat.y = q1.y * (1 - x) + q2.y * x;
	returnQuat.z = q1.z * (1 - x) + q2.z * x;
	return returnQuat;
}

Pose interpolatePoseLinear(Pose pose1, Pose pose2, float x){
	assert(pose1.getNumBones() == pose2.getNumBones());
	Vector::quat quatArray[pose1.getNumBones()];
	Vector::quat * pose1Array = pose1.getQuatArray();
	Vector::quat * pose2Array = pose2.getQuatArray();
	for(int i = 0; i < pose1.getNumBones(); ++i){
		quatArray[i] = interpolateQuatLinear(pose1Array[i], pose2Array[i], x);
	}
	return Pose(quatArray, pose1.getNumBones());
}

} /* namespace ts */
