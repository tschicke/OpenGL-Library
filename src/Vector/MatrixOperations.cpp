/*
 * MatrixOperations.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: tyler
 */

#include "MatrixOperations.h"

namespace ts {
namespace Vector {

mat4 transpose(mat4 matrix) {
	mat4 result(matrix);
	result[0][0] = matrix[0][0];
	result[0][1] = matrix[1][0];
	result[0][2] = matrix[2][0];
	result[0][3] = matrix[3][0];

	result[1][0] = matrix[0][1];
	result[1][1] = matrix[1][1];
	result[1][2] = matrix[2][1];
	result[1][3] = matrix[3][1];

	result[2][0] = matrix[0][2];
	result[2][1] = matrix[1][2];
	result[2][2] = matrix[2][2];
	result[2][3] = matrix[3][2];

	result[3][0] = matrix[0][3];
	result[3][1] = matrix[1][3];
	result[3][2] = matrix[2][3];
	result[3][3] = matrix[3][3];
	return result;
}

float determinant(mat4 matrix) {
	/*
	 * [a, b, c, d]
	 * [e, f, g, h]
	 * [i, j, k, l]
	 * [m, n, o, p]
	 */
	float subSubDet01 = matrix[2][0] * matrix[3][1] - matrix[3][0] * matrix[2][1];//ch - dg
	float subSubDet02 = matrix[2][0] * matrix[3][2] - matrix[3][0] * matrix[2][2];//cl - dk
	float subSubDet03 = matrix[2][0] * matrix[3][3] - matrix[3][0] * matrix[2][3];//cp - do
	float subSubDet12 = matrix[2][1] * matrix[3][2] - matrix[3][1] * matrix[2][2];//gl - hk
	float subSubDet13 = matrix[2][1] * matrix[3][3] - matrix[3][1] * matrix[2][3];//gp - ho
	float subSubDet23 = matrix[2][2] * matrix[3][3] - matrix[3][2] * matrix[2][3];//kp - lo

	float subDet012 = matrix[1][0] * subSubDet12 - matrix[1][1] * subSubDet02 + matrix[1][2] * subSubDet01;//b(gl - hk) - f(cl - dk) + j(ch - dg)
	float subDet013 = matrix[1][0] * subSubDet13 - matrix[1][1] * subSubDet03 + matrix[1][3] * subSubDet01;//b(gp - ho) - f(cp - do) + n(ch - dg)
	float subDet023 = matrix[1][0] * subSubDet23 - matrix[1][2] * subSubDet03 + matrix[1][3] * subSubDet02;//b(kp - lo) - j(cp - do) + n(cl - dk)
	float subDet123 = matrix[1][1] * subSubDet23 - matrix[1][2] * subSubDet13 + matrix[1][3] * subSubDet12;//f(kp - lo) - j(gp - ho) + n(gl - hk)

	return matrix[0][0] * subDet123 - matrix[0][1] * subDet023 + matrix[0][2] * subDet013 - matrix[0][3] * subDet012;
}

} /* namespace Vector */
} /* namespace ts */
