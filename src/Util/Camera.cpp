/*
 * Camera.cpp
 *
 *  Created on: May 19, 2014
 *      Author: tyler
 */

#include "Camera.h"

#include "../Vector/QuaternionOperations.h"

namespace ts {
namespace Vector {

Camera::Camera() {
	init(ts::Vector::vec3(0, 0, 0));
}

Camera::Camera(ts::Vector::vec3 position) {
	init(position);
}

void Camera::init(ts::Vector::vec3 position) {
	this->position = position;
	rotation = ts::Vector::quat(1, 0, 0, 0);
	viewMatrixNeedsUpdate = true;
}

Camera::~Camera() {
}

void Camera::rotateLocal(float angle, float axisX, float axisY, float axisZ) {
	rotation = rotation * angleAxisToQuaternion(angle, axisX, axisY, axisZ);
}

void Camera::rotateLocal(float angle, ts::Vector::vec3 axis) {
	rotation = rotation * angleAxisToQuaternion(angle, axis);
}

void Camera::rotateGlobal(float angle, float axisX, float axisY, float axisZ) {
	rotation = angleAxisToQuaternion(angle, axisX, axisY, axisZ) * rotation;
}

void Camera::rotateGlobal(float angle, ts::Vector::vec3 axis) {
	rotation = angleAxisToQuaternion(angle, axis) * rotation;
}

void Camera::lookAt(float x, float y, float z) {
}

void Camera::lookAt(ts::Vector::vec3 position) {
}

void Camera::move(ts::Vector::vec3 moveVector) {
	position += moveVector;
}

void Camera::move(float dx, float dy, float dz) {
	position += ts::Vector::vec3(dx, dy, dz);
}

void Camera::moveInDirection(ts::Vector::vec3 moveVector) {
}

void Camera::moveInDirection(float dx, float dy, float dz) {
}

void Camera::setPosition(ts::Vector::vec3 newPosition) {
	position = newPosition;
}

void Camera::setPosition(float x, float y, float z) {
	position = ts::Vector::vec3(x, y, z);
}

void Camera::setX(float x) {
	position.x = x;
}

void Camera::setY(float y) {
	position.y = y;
}

void Camera::setZ(float z) {
	position.z = z;
}

ts::Vector::vec3 Camera::getPosition() {
	return position;
}

ts::Vector::mat4* Camera::getViewMatrix() {

}

} /* namespace Vector */
} /* namespace ts */
