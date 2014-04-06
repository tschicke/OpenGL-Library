/*
 * VectorOperations.h
 *
 *  Created on: Apr 5, 2014
 *      Author: tyler
 */

#ifndef O_H_
#define O_H_

#include "Vector.h"

namespace ts {
namespace Vector {

	float dot(vec2 v1, vec2 v2);
	float dot(vec3 v1, vec3 v2);

	vec3 cross(vec3 v1, vec3 v2);

//	float length(vec2 v1);
	float length(vec3 v1);

//	float distance(vec2 v1, vec2 v2);
	float distance(vec3 v1, vec3 v2);

//	vec2 normalize(vec2 v1);
	vec3 normalize(vec3 v1);

} /* namespace Vector */
} /* namespace ts */
#endif /* O_H_ */
