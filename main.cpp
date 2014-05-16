/*
 * main.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "src/Window/Window.h"

#include "src/Window/TestScene.h"

#include "src/Vector/Quaternion.h"
#include "src/Vector/QuaternionOperations.h"
#include "src/Vector/Matrix.h"
#include "src/Vector/MatrixTransform.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

int main() {
//	ts::Vector::Quaternion q1(1, 2, 3, 4);
//	ts::Vector::Quaternion q2(2, 3, 4, 1);

//	(q1 * q2).print();

//	glm::quat quaternion = glm::angleAxis(120.f, glm::vec3(1, 1, 1));

//	std::cout << quaternion.w << ' ' << quaternion.x << ' ' << quaternion.y << ' ' << quaternion.z << '\n';

//	ts::Vector::mat4 matrix = ts::Vector::translate(1, 2, 4);
//	ts::Vector::mat4 matrix2 = ts::Vector::ortho(-2, 2, -2, 2, 1, 100);
//
//	(matrix * matrix2).print();
//
//	glm::mat4 mat1 = glm::translate(1.f, 2.f, 4.f);
//	glm::mat4 mat2 = glm::ortho(-2.f, 2.f, -2.f, 2.f, 1.f, 100.f);
//	glm::mat4 mat3= mat1 * mat2;
//
//	for(int y = 0; y < 4; ++y){
//		for(int x = 0; x < 4; ++x){
//			std::cout << mat3[x][y] << ' ';
//		}
//		std::cout << '\n';
//	}

	ts::Window * mainWindow = ts::Window::getMainWindow();
	mainWindow->create(1280, 720, 90, "OGL Lib");
	mainWindow->setBackgroundColorf(0.5f, 0.5f, 0.5f);
	mainWindow->setScene(new ts::TestScene);
	mainWindow->start();
}

