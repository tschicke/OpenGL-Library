/*
 * MatrixOperations.h
 *
 *  Created on: Apr 6, 2014
 *      Author: tyler
 */

#ifndef MATRIXOPERATIONS_H_
#define MATRIXOPERATIONS_H_

#include "Matrix.h"

namespace ts {
namespace Vector {

mat4 transpose(mat4 matrix);

float determinant(mat4 matrix);

mat4 inverse(mat4 matrix);

} /* namespace Vector */
} /* namespace ts */
#endif /* MATRIXOPERATIONS_H_ */
