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
#include "src/Vector/VectorOperations.h"
#include "src/Vector/Quaternion.h"
#include "src/Vector/QuaternionOperations.h"
#include "src/Vector/Matrix.h"
#include "src/Vector/MatrixTransform.h"

using namespace ts::Vector;

int main() {
	ts::Window * mainWindow = ts::Window::getMainWindow();
	mainWindow->create(1280, 720, 90, "OGL Lib");
	mainWindow->setBackgroundColorf(0.5f, 0.5f, 0.5f);
	mainWindow->setScene(new ts::TestScene);
	mainWindow->start();
}

