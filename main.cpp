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

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

int main() {
	ts::Vector::Quaternion q1(1, 2, 3, 4);
	ts::Vector::Quaternion q2(2, 3, 4, 1);

//	(q1 * q2).print();

//	glm::quat quaternion = glm::angleAxis(120.f, glm::vec3(1, 1, 1));

//	std::cout << quaternion.w << ' ' << quaternion.x << ' ' << quaternion.y << ' ' << quaternion.z << '\n';

//	ts::Window * mainWindow = ts::Window::getMainWindow();
//	mainWindow->create(1280, 720, 90, "OGL Lib");
//	mainWindow->setBackgroundColorf(0.5f, 0.5f, 0.5f);
//	mainWindow->setScene(new ts::TestScene);
//	mainWindow->start();
}

