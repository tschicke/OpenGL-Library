/*
 * TestScene.h
 *
 *  Created on: Feb 11, 2014
 *      Author: Tyler
 */

#ifndef TESTSCENE_H_
#define TESTSCENE_H_

#include "Scene.h"

#include "../Util/Camera.h"
#include "../Render/Model.h"

#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"

namespace ts {

class TestScene : public Scene{
public:
	TestScene();
	virtual ~TestScene();

	void update(time_t dt);
	void draw();
private:
	float cameraSpeed;
	Camera camera;
	Model model, model2;
	Model plane;
};

} /* namespace ts */
#endif /* TESTSCENE_H_ */
