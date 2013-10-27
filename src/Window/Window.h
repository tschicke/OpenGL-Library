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

	void setBackgroundColorb(ubyte r, ubyte g, ubyte b);
	void setBackgroundColorf(float r, float g, float b);

	using sf::Window::create;

protected:
	void initGL();
	void init();

	bool running;
	void run();

	void updateInput();
	void update(time_t dt);
	void render();

	void cleanUp();

	Scene * currentScene;

	sf::Clock clock;

	int width, height;
};

} /* namespace ts */
#endif /* WINDOW_H_ */
