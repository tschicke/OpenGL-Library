/*
 * Scene.h
 *
 *  Created on: Oct 6, 2013
 *      Author: Tyler
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "../Common.h"

namespace ts {

class Scene {
public:
	Scene();
	virtual ~Scene();

	virtual void update(time_t dt) = 0;
	virtual void draw() = 0;

	virtual void cleanUp();
};

} /* namespace ts */
#endif /* SCENE_H_ */
