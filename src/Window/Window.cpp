/*
 * Window.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: Tyler
 */

#include "Window.h"

#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Scene.h"

#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"

#include "../Util/MathHelper.h"

#include <iostream>

#include "../Render/ResourceManager.h"

namespace ts {

Window * Window::mainWindow = new Window;

Window* Window::getMainWindow() {
	return mainWindow;
}

Window::Window() {
	width = height = 0;
	FOV = 90;
	running = false;
	currentScene = NULL;
	printFPS = true;
}

Window::Window(int width, int height, int FOV, const char* title) {
	create(width, height, FOV, title);
}

Window::~Window() {
}

void Window::create(int width, int height, int FOV, const char* title) {
	this->width = width;
	this->height = height;
	this->FOV = FOV;
	projectionMatrix = glm::perspective((float) FOV, (float) width / (float) height, 0.1f, 2000.f);
	running = false;
	printFPS = true;
	create(sf::VideoMode(width, height, 32), title);
	setFramerateLimit(60); //TODO make way of changing this
	initGL();
	init();
	setBackgroundColorf(1.f, 1.f, 1.f);
}

void Window::init() {
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
		currentScene->cleanUp();
		delete currentScene;
	}
	currentScene = newScene;
}

void Window::run() {
	long counter = 0;
	int frames = 0;
	while (running) {
		long dt = clock.restart().asMicroseconds();
		counter += dt;
		frames++;
		if (counter >= 1000000) {
			if (printFPS) {
				std::cout << frames << std::endl;
			}
			counter = 0;
			frames = 0;
		}

		updateInput();
		update(dt);
		render();
	}
	cleanUp();
}

void Window::updateInput() {
	Keyboard::clearEvents();
	Mouse::clear();
	Mouse::setLastMove(0, 0);
	sf::Event event;
	while (pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			stop();
		} else if (event.type == sf::Event::KeyPressed) {
			Keyboard::setKey(event.key.code, true);
			Keyboard::setKeyEvent(event.key.code, Keyboard::keyPressed);
		} else if (event.type == sf::Event::KeyReleased) {
			Keyboard::setKey(event.key.code, false);
			Keyboard::setKeyEvent(event.key.code, Keyboard::keyReleased);
		} else if (event.type == sf::Event::MouseButtonPressed) {
			Mouse::setMouseButton(event.mouseButton.button, true);
			Mouse::setMouseButtonEvent(event.mouseButton.button, Mouse::buttonPressed);
		} else if (event.type == sf::Event::MouseButtonReleased) {
			Mouse::setMouseButton(event.mouseButton.button, false);
			Mouse::setMouseButtonEvent(event.mouseButton.button, Mouse::buttonReleased);
		} else if (event.type == sf::Event::MouseMoved) {
			int dx = 0, dy = 0;
			dx = (event.mouseMove.x - Mouse::getPosition().x);
			dy = -(event.mouseMove.y - (height - Mouse::getPosition().y));
			Mouse::setLastMove(dx, dy);
			Mouse::setPosition(event.mouseMove.x, height - event.mouseMove.y);
		} else if (event.type == sf::Event::MouseWheelMoved) {
			Mouse::setMouseWheelDelta(event.mouseWheel.delta);
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
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Glew not initialized properly\n";
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Window::setFOV(int FOV) {
	this->FOV = FOV;
}

glm::mat4* Window::getProjectionMatrix() {
	return &projectionMatrix;
}

void Window::cleanUp() {
	if (currentScene != NULL) {
		currentScene->cleanUp();
		delete currentScene;
	}

	MathHelper::cleanup();
}

} /* namespace ts */
