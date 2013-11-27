/*
 * Camera.h
 *
 *  Created on: Oct 26, 2013
 *      Author: Tyler
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>

namespace ts {

class Camera {
public:
	Camera();
	Camera(glm::vec3 position);
	void init(glm::vec3 position);
	virtual ~Camera();

	void rotate(int dx, int dy);
	void move(glm::vec3 moveVector);
	void move(float dx, float dy, float dz);

	void setPosition(glm::vec3 newPosition);
	void setPosition(int x, int y, int z);

	glm::vec3 getPosition();
	glm::vec3 getDirection();
	glm::mat4 * getViewMatrix();
private:
	glm::vec3 position;
	glm::vec3 lookDir;
	glm::mat4 viewMatrix;

	int yaw, pitch;

	bool viewMatrixNeedsUpdate;
};

} /* namespace ts */
#endif /* CAMERA_H_ */
