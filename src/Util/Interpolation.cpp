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

float interpolateLinear(float n1, float n2, float x) {
	return n1 * (1 - x) + n2 * x;
}

float interpolateCubic(float n0, float n1, float n2, float n3, float x) {
	float p = (n3 - n2) - (n0 - n1);
	float q = 2 * (n0 - n1) - (n3 - n2);
	float r = n2 - n0;
	float s = n1;

	float xSquared = x * x;
	float xCubed = xSquared * x;

	return p * xCubed + q * xSquared + r * x + s;
}

Vector::quat interpolateQuatLinear(Vector::quat q1, Vector::quat q2, float x) {
	Vector::quat returnQuat;
	returnQuat.w = interpolateLinear(q1.w, q2.w, x);
	returnQuat.x = interpolateLinear(q1.x, q2.x, x);
	returnQuat.y = interpolateLinear(q1.y, q2.y, x);
	returnQuat.z = interpolateLinear(q1.z, q2.z, x);
	return returnQuat;
}

Vector::quat interpolateQuatCubic(Vector::quat q0, Vector::quat q1, Vector::quat q2, Vector::quat q3, float x) {
	Vector::quat returnQuat;
	returnQuat.w = interpolateCubic(q0.w, q1.w, q2.w, q3.w, x);
	returnQuat.x = interpolateCubic(q0.x, q1.x, q2.x, q3.x, x);
	returnQuat.y = interpolateCubic(q0.y, q1.y, q2.y, q3.y, x);
	returnQuat.z = interpolateCubic(q0.z, q1.z, q2.z, q3.z, x);
	return returnQuat;
}

Pose interpolatePoseLinear(Pose pose1, Pose pose2, float x) {
	assert(pose1.getNumBones() == pose2.getNumBones());
	Vector::quat quatArray[pose1.getNumBones()];
	Vector::quat * pose1Array = pose1.getQuatArray();
	Vector::quat * pose2Array = pose2.getQuatArray();
	for (int i = 0; i < pose1.getNumBones(); ++i) {
		quatArray[i] = interpolateQuatLinear(pose1Array[i], pose2Array[i], x);
	}
	return Pose(quatArray, pose1.getNumBones());
}

Pose interpolatePoseCubic(Pose pose0, Pose pose1, Pose pose2, Pose pose3, float x) {
	assert(pose1.getNumBones() == pose2.getNumBones() && pose1.getNumBones() == pose3.getNumBones() && pose1.getNumBones() == pose0.getNumBones());
	Vector::quat quatArray[pose1.getNumBones()];
	Vector::quat * pose0Array = pose0.getQuatArray();
	Vector::quat * pose1Array = pose1.getQuatArray();
	Vector::quat * pose2Array = pose2.getQuatArray();
	Vector::quat * pose3Array = pose3.getQuatArray();
	for (int i = 0; i < pose1.getNumBones(); ++i) {
		quatArray[i] = interpolateQuatCubic(pose0Array[i], pose1Array[i], pose2Array[i], pose3Array[i], x);
	}
	return Pose(quatArray, pose1.getNumBones());
}

} /* namespace ts */
