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

#include "../Render/Model.h"
#include "../Util/Camera.h"

#include <glm/glm.hpp>

namespace ts {

class Scene;

class Window : public sf::Window{
public:
	Window();
	Window(int width, int height, int FOV, const char * title);
	virtual ~Window();

	static Window * getMainWindow();

	void create(int width, int height, int FOV, const char * title);

	void start();
	void stop();

	void setScene(Scene * newScene);

	void setBackgroundColorb(ubyte r, ubyte g, ubyte b);
	void setBackgroundColorf(float r, float g, float b);

	void setFOV(int FOV);

	glm::mat4 * getProjectionMatrix();

	using sf::Window::create;

protected:
	static Window * mainWindow;

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
	int FOV;
	bool printFPS;

	glm::mat4 projectionMatrix;

	Model testModel;
	Camera testCamera;
};

} /* namespace ts */
#endif /* WINDOW_H_ */
