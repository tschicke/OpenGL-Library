/*
 * MatrixTransform.h
 *
 *  Created on: Apr 12, 2014
 *      Author: tyler
 */

#ifndef MATRIXTRANSFORM_H_
#define MATRIXTRANSFORM_H_

#include "Matrix.h"
#include "Vector.h"

namespace ts {
namespace Vector {

mat4 ortho(float left, float right, float bottom, float top, float near, float far);
mat4 frustrum(float left, float right, float bottom, float top, float near, float far);
mat4 perspective(float fov, float width, float height, float near, float far);

mat4 lookAt(vec3 cameraPosition, vec3 lookCenter, vec3 up);
mat4 lookAt(vec3 cameraPosition, float yaw, float pitch, float roll);

mat4 translate(float x, float y, float z);
mat4 translate(vec3 translateVector);
mat4 scale(float x, float y, float z);
mat4 scale(vec3 scaleVector);


} /* namespace Vector */
} /* namespace ts */
#endif /* MATRIXTRANSFORM_H_ */
