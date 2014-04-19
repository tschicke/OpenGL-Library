/*
 * main.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "src/Window/Window.h"

#include "src/Window/TestScene.h"

#include "src/Vector/Vector.h"
#include "src/Vector/Matrix.h"
#include "src/Vector/MatrixOperations.h"
#include "src/Vector/MatrixTransform.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

int main() {
//	float x = 11, y = 11, z = 0;
//	glm::mat4 testMatrix = glm::perspectiveFov(58.72f, 1280.f, 720.f, 1.f, 100.f);
//	glm::vec4 testVector = (testMatrix * glm::vec4(x, y, z, 1.f));
//	ts::Vector::mat4 testMatrix2 = ts::Vector::perspective(90.f, 1280.f, 720.f, 1.f, 100.f);
//	ts::Vector::vec4 testVector2 = testMatrix2 * ts::Vector::vec4(x, y, z, 1.f);
//
//	testMatrix2.print();
//	std::cout << '\n';
//
//	for (int y = 0; y < 4; ++y) {
//		for (int x = 0; x < 4; ++x) {
//			std::cout << testMatrix[x][y] << ' ';
//		}
//		std::cout << '\n';
//	}
//
//	for (int y = 0; y < 4; ++y) {
//		for (int x = 0; x < 4; ++x) {
//			std::cout << test2[x][y] << ' ';
//		}
//		std::cout << '\n';
//	}

	ts::Window * mainWindow = ts::Window::getMainWindow();
	mainWindow->create(1280, 720, 90, "OGL Lib");
	mainWindow->setBackgroundColorf(0.5f, 0.5f, 0.5f);
	mainWindow->setScene(new ts::TestScene);
	mainWindow->start();
}

