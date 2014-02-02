/*
 * MathHelper.h
 *
 *  Created on: Jul 29, 2013
 *      Author: Tyler
 */

#ifndef MATHHELPER_H_
#define MATHHELPER_H_

#define MATH_PI 3.14159265f

class MathHelper {
public:
	static void init();
	static void cleanup();

	static float sin_float(float angle);
	static float cos_float(float angle);

	static float toRadians(float degrees);
	static float toDegrees(float radians);

	static int max(int a, int b);
	static float maxf(float a, float b);
	static int min(int a, int b);
	static float minf(float a, float b);
private:
	MathHelper(){};
	virtual ~MathHelper(){};

	static float * SIN_TABLE;
};

#endif /* MATHHELPER_H_ */
