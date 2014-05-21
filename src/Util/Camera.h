/*
 * Camera.h
 *
 *  Created on: May 19, 2014
 *      Author: tyler
 */

#include "../Vector/Vector.h"
#include "../Vector/Matrix.h"
#include "../Vector/Quaternion.h"

#ifndef CAMERA_H_
#define CAMERA_H_

namespace ts {

class Camera {
public:
	Camera();
	Camera(ts::Vector::vec3 position);
	void init(ts::Vector::vec3 position);
	virtual ~Camera();

	void rotateGlobal(float angle, float xAxis, float yAxis, float zAxis);
	void rotateGlobal(float angle, ts::Vector::vec3 axis);
	void rotateLocal(float angle, float xAxis, float yAxis, float zAxis);
	void rotateLocal(float angle, ts::Vector::vec3 axis);
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

	ts::Vector::vec3 getPosition();
	ts::Vector::mat4 * getViewMatrix();
	private:
	ts::Vector::vec3 position;
	ts::Vector::quat rotation;
	ts::Vector::mat4 viewMatrix;

	bool viewMatrixNeedsUpdate;
};

} /* namespace ts */
#endif /* CAMERA_H_ */
