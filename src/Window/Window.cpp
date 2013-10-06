/*
 * Window.cpp
 *
 *  Created on: Oct 6, 2013
 *      Author: Tyler
 */

#include "Window.h"

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
	sf::Event event;
	while(pollEvent(event)){
		if(event.type == sf::Event::Closed){
			stop();
		} else if(event.type == sf::Event::KeyPressed){

		} else if(event.type == sf::Event::KeyReleased){

		} else if(event.type == sf::Event::MouseButtonPressed){

		} else if(event.type == sf::Event::MouseButtonReleased){

		} else if(event.type == sf::Event::MouseMoved){

		} else if(event.type == sf::Event::MouseWheelMoved){

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

} /* namespace ts */
