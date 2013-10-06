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
	window.start();
}

