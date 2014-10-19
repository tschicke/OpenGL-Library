/*
 * Interpolation.h
 *
 *  Created on: Oct 3, 2014
 *      Author: Tyler
 */

#ifndef INTERPOLATION_H_
#define INTERPOLATION_H_

#include "../Render/AnimatedMesh.h"

namespace ts {

float interpolateLinear(float n1, float n2, float x);
float interpolateCubic(float n0, float n1, float n2, float n3, float x);

Vector::quat interpolateQuatLinear(Vector::quat q1, Vector::quat q2, float x);
Vector::quat interpolateQuatCubic(Vector::quat q0, Vector::quat q1, Vector::quat q2, Vector::quat q3, float x);

Pose interpolatePoseLinear(Pose pose1, Pose pose2, float x);
Pose interpolatePoseCubic(Pose pose0, Pose pose1, Pose pose2, Pose pose3, float x);

} /* namespace ts */

#endif /* INTERPOLATION_H_ */
