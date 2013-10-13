/*
 * Window.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: Tyler
 */

#include "Window.h"

#include <gl/gl.h>
#include <gl/glew.h>

#include "Scene.h"

#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"

namespace ts {

Window::Window() {
	running = false;
	currentScene = NULL;
}

Window::Window(int width, int height, const char* title) {
	create(width, height, title);
}

Window::~Window() {
}

void Window::create(int width, int height, const char* title) {
	create(sf::VideoMode(width, height, 32), title);
}

void Window::start() {
	running = true;
	run();
}

void Window::stop() {
	running = false;
}

void Window::setScene(Scene* newScene) {
	if(newScene == NULL){
		return;
	}
	if(currentScene != NULL){
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
}

void Window::updateInput() {
	ts::Keyboard::clearEvents();
	ts::Mouse::clear();
	sf::Event event;
	while(pollEvent(event)){
		if(event.type == sf::Event::Closed){
			stop();
		} else if(event.type == sf::Event::KeyPressed){
			ts::Keyboard::setKey(event.key.code, true);
			ts::Keyboard::setKeyEvent(event.key.code, ts::Keyboard::keyPressed);
		} else if(event.type == sf::Event::KeyReleased){
			ts::Keyboard::setKey(event.key.code, false);
			ts::Keyboard::setKeyEvent(event.key.code, ts::Keyboard::keyReleased);
		} else if(event.type == sf::Event::MouseButtonPressed){
			ts::Mouse::setMouseButton(event.mouseButton.button, true);
			ts::Mouse::setMouseButtonEvent(event.mouseButton.button, ts::Mouse::buttonPressed);
		} else if(event.type == sf::Event::MouseButtonReleased){
			ts::Mouse::setMouseButton(event.mouseButton.button, false);
			ts::Mouse::setMouseButtonEvent(event.mouseButton.button, ts::Mouse::buttonReleased);
		} else if(event.type == sf::Event::MouseMoved){
			ts::Mouse::setPosition(event.mouseMove.x, event.mouseMove.y);
		} else if(event.type == sf::Event::MouseWheelMoved){
			ts::Mouse::setMouseWheelDelta(event.mouseWheel.delta);
		}
	}
}

void Window::update(time_t dt) {
	if(currentScene != NULL){
		currentScene->update(dt);
	}
}

void Window::render() {
	if(currentScene != NULL){
		currentScene->draw();
	}
}

void Window::initGL(){
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK){
		std::cerr << "Glew not initialized properly\n";
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);

}

} /* namespace ts */
