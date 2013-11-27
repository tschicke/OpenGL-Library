/*
 * Window.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: Tyler
 */

#include "Window.h"

#include <gl/glew.h>

#include "Scene.h"

#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"

#include "../Util/MathHelper.h"

#include <iostream>

namespace ts {

Window::Window() {
	width = height = 0;
	running = false;
	currentScene = NULL;
}

Window::Window(int width, int height, const char* title) {
	create(width, height, title);
}

Window::~Window() {
}

void Window::create(int width, int height, const char* title) {
	this->width = width;
	this->height = height;
	running = false;
	create(sf::VideoMode(width, height, 32), title);
	initGL();
	init();
	setBackgroundColorf(1.f, 1.f, 1.f);
}

void Window::init(){
	MathHelper::init();
}

void Window::start() {
	running = true;
	run();
}

void Window::stop() {
	running = false;
}

void Window::setScene(Scene* newScene) {
	if (newScene == NULL) {
		return;
	}
	if (currentScene != NULL) {
		delete currentScene;
	}
	currentScene = newScene;
}

void Window::run() {
	while (running) {
		updateInput();
		update(clock.restart().asMilliseconds());
		render();
	}
	cleanUp();
}

void Window::updateInput() {
	ts::Keyboard::clearEvents();
	ts::Mouse::clear();
	sf::Event event;
	while (pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			stop();
		} else if (event.type == sf::Event::KeyPressed) {
			ts::Keyboard::setKey(event.key.code, true);
			ts::Keyboard::setKeyEvent(event.key.code, ts::Keyboard::keyPressed);
		} else if (event.type == sf::Event::KeyReleased) {
			ts::Keyboard::setKey(event.key.code, false);
			ts::Keyboard::setKeyEvent(event.key.code, ts::Keyboard::keyReleased);
		} else if (event.type == sf::Event::MouseButtonPressed) {
			ts::Mouse::setMouseButton(event.mouseButton.button, true);
			ts::Mouse::setMouseButtonEvent(event.mouseButton.button, ts::Mouse::buttonPressed);
		} else if (event.type == sf::Event::MouseButtonReleased) {
			ts::Mouse::setMouseButton(event.mouseButton.button, false);
			ts::Mouse::setMouseButtonEvent(event.mouseButton.button, ts::Mouse::buttonReleased);
		} else if (event.type == sf::Event::MouseMoved) {
			ts::Mouse::setPosition(event.mouseMove.x, event.mouseMove.y);
		} else if (event.type == sf::Event::MouseWheelMoved) {
			ts::Mouse::setMouseWheelDelta(event.mouseWheel.delta);
		}
	}
}

void Window::update(time_t dt) {
	if (currentScene != NULL) {
		currentScene->update(dt);
	}
}

void Window::setBackgroundColorb(ubyte r, ubyte g, ubyte b) {
	r = (r < 0 ? 0 : (r > 255 ? 255 : r));
	g = (g < 0 ? 0 : (g > 255 ? 255 : g));
	b = (b < 0 ? 0 : (b > 255 ? 255 : b));
	glClearColor(r / 255.f, g / 255.f, b / 255.f, 1);
}

void Window::setBackgroundColorf(float r, float g, float b) {
	r = (r < 0 ? 0 : (r > 1.f ? 1.f : r));
	g = (g < 0 ? 0 : (g > 1.f ? 1.f : g));
	b = (b < 0 ? 0 : (b > 1.f ? 1.f : b));
	glClearColor(r, g, b, 1);
}

void Window::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (currentScene != NULL) {
		currentScene->draw();
	}
	display();
}

void Window::initGL() {
	glEnable(GL_DEPTH_TEST);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Glew not initialized properly\n";
		exit(EXIT_FAILURE);
	}
}

void Window::cleanUp() {
	delete currentScene;

	MathHelper::cleanup();
}

} /* namespace ts */
