/*
 * Window.h
 *
 *  Created on: Oct 6, 2013
 *      Author: Tyler
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <SFML/Window.hpp>

#include "../Common.h"

namespace ts {

class Scene;

class Window : public sf::Window{
public:
	Window();
	Window(int width, int height, const char * title);
	virtual ~Window();

	void create(int width, int height, const char * title);

	void start();
	void stop();

	void setScene(Scene * newScene);

	using sf::Window::create;

protected:
	void initGL();

	bool running;
	void run();

	void updateInput();
	void update(time_t dt);
	void render();

	Scene * currentScene;

	sf::Clock clock;
};

} /* namespace ts */
#endif /* WINDOW_H_ */
