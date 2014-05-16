/*
 * Camera.h
 *
 *  Created on: Oct 26, 2013
 *      Author: Tyler
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Vector/Vector.h"
#include "../Vector/Matrix.h"

namespace ts {

class Camera {
public:
	Camera();
	Camera(ts::Vector::vec3 position);
	void init(ts::Vector::vec3 position);
	virtual ~Camera();

	void rotate(int dx, int dy);
	void lookAt(float x, float y, float z);
	void lookAt(ts::Vector::vec3 position);
	void move(ts::Vector::vec3 moveVector);
	void move(float dx, float dy, float dz);
	void moveInDirection(ts::Vector::vec3 moveVector);
	void moveInDirection(float dx, float dy, float dz);

	void setPosition(ts::Vector::vec3 newPosition);
	void setPosition(float x, float y, float z);
	void setX(float x);
	void setY(float y);
	void setZ(float z);

	void addRoll(int add);

	ts::Vector::vec3 getPosition();
	ts::Vector::vec3 getDirection();
	ts::Vector::mat4 * getViewMatrix();
private:
	ts::Vector::vec3 position;
	ts::Vector::vec3 lookDir;
	ts::Vector::vec3 upVector;
	ts::Vector::mat4 viewMatrix;

	int yaw, pitch, roll;

	bool viewMatrixNeedsUpdate;
};

} /* namespace ts */
#endif /* CAMERA_H_ */
