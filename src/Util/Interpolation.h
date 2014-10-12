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


Vector::quat interpolateQuatLinear(Vector::quat q1, Vector::quat q2, float x);
Pose interpolatePoseLinear(Pose pose1, Pose pose2, float x);

} /* namespace ts */

#endif /* INTERPOLATION_H_ */
