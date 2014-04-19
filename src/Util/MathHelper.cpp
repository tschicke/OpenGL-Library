/*
 * MathHelper.cpp
 *
 *  Created on: Jul 29, 2013
 *      Author: Tyler
 */

#include "MathHelper.h"
#include <cmath>

float * MathHelper::SIN_TABLE = 0;

void MathHelper::init() {
	SIN_TABLE = new float[3600];

	for (int i = 0; i < 3600; ++i) {
		SIN_TABLE[i] = sin(i * 2.f * MATH_PI / 3600.f);
	}
}

void MathHelper::cleanup() {
	delete SIN_TABLE;
}

//Returns sine of angle (in radians)
float MathHelper::sin_float(float angle) {
	angle = fmod(angle, 2.0 * MATH_PI);
	if (angle < 0) {
		angle += 2.f * MATH_PI;
	}
	return SIN_TABLE[(int) (angle * 572.9578f)];
}

//Returns cosine of and (in radians)
float MathHelper::cos_float(float angle) {
	angle += toRadians(90);
	angle = fmod(angle, 2.0 * MATH_PI);
	if (angle < 0) {
		angle += 2.f * MATH_PI;
	}
	return SIN_TABLE[(int) (angle * 572.9578f)];
}

float MathHelper::toRadians(float degrees) {
	return degrees * MATH_PI / 180.f;
}

float MathHelper::toDegrees(float radians) {
	return radians * 180.f / MATH_PI;
}

//Returns the larger of a and b. If a and b are equal, returns b.
int MathHelper::max(int a, int b) {
	return (a > b ? a : b);
}

//Returns the larger of a and b. If a and b are equal, returns b.
float MathHelper::maxf(float a, float b) {
	return (a > b ? a : b);
}

//Returns the smaller of a and b. If a and b are equal, returns b.
int MathHelper::min(int a, int b) {
	return (a < b ? a : b);

}

//Returns the smaller of a and b. If a and b are equal, returns b.
float MathHelper::minf(float a, float b) {
	return (a < b ? a : b);

}
