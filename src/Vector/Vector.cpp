/*
 * Vector.cpp
 *
 *  Created on: Apr 2, 2014
 *      Author: tyler
 */

#include <iostream>

#include "Vector.h"

namespace ts {
namespace Vector{

Vector2::Vector2() {
	x = y = 0;
}

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector3::Vector3() {
	x = y = z = 0;
}

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float& Vector3::operator [](std::size_t index){
	if(index >= 3 || index < 0){
		std::cerr << "Error accessing vector: index out of bounds" << std::endl;
	}
	return (&x)[index];
}

const float& Vector3::operator [](std::size_t index) const {
	return const_cast<Vector3&>(*this)[index];
}


}
 /* namespace Vector */
} /* namespace ts */
