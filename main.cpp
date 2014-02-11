/*
 * main.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: Tyler
 */

#include "src/Window/Window.h"

int main(){
	ts::Window * mainWindow = ts::Window::getMainWindow();
	mainWindow->create(1280, 720, 90, "OGL Lib");
	mainWindow->setBackgroundColorf(0.5f, 0.5f, 0.5f);
	mainWindow->start();
}

