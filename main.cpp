/*
 * main.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: Tyler
 */

#include "src/Window/Window.h"

int main(){
	ts::Window window;
	window.create(1280, 720, "OGL Lib");
	window.setBackgroundColorf(0.5f, 0.5f, 0.5f);
	window.start();
}

