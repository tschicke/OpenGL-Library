/*
 * VectorOperations.cpp
 *
 *  Created on: Apr 5, 2014
 *      Author: tyler
 */

#include "VectorOperations.h"

#include <cmath>

namespace ts {
namespace Vector {

float dot(vec2 v1, vec2 v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

float dot(vec3 v1, vec3 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3 cross(vec3 v1, vec3 v2) {
	float x = v1.y * v2.z - v1.z * v2.y;
	float y = v1.z * v2.x - v1.x * v2.z;
	float z = v1.x * v2.y - v1.y * v2.x;
	return vec3(x, y, z);
}

//float length(vec2 v1) {
//	return std::sqrt((v1.x * v1.x) + (v1.y * v1.y));
//}

float length(vec3 v1) {
	return std::sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
}

//float distance(vec2 v1, vec2 v2) {
//	return length(v2 - v1);
//}

float distance(vec3 v1, vec3 v2) {
	return length(v2 - v1);
}

vec3 normalize(vec3 v1) {
	return v1 / length(v1);
}

} /* namespace Vector */
} /* namespace ts */
