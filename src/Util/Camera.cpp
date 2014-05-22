/*
 * Camera.cpp
 *
 *  Created on: May 19, 2014
 *      Author: tyler
 */

#include "Camera.h"

#include "../Vector/QuaternionOperations.h"
#include "../Vector/MatrixTransform.h"

namespace ts {

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

void Camera::rotateGlobal(float angle, float axisX, float axisY, float axisZ) {
	rotation = rotation * ts::Vector::angleAxisToQuaternion(angle, axisX, axisY, axisZ);
	viewMatrixNeedsUpdate = true;
}

void Camera::rotateGlobal(float angle, ts::Vector::vec3 axis) {
	rotation = rotation * ts::Vector::angleAxisToQuaternion(angle, axis);
	viewMatrixNeedsUpdate = true;
}

void Camera::rotateLocal(float angle, float axisX, float axisY, float axisZ) {
	rotation = ts::Vector::angleAxisToQuaternion(angle, axisX, axisY, axisZ) * rotation;
	viewMatrixNeedsUpdate = true;
}

void Camera::rotateLocal(float angle, ts::Vector::vec3 axis) {
	rotation = ts::Vector::angleAxisToQuaternion(angle, axis) * rotation;
	viewMatrixNeedsUpdate = true;
}

void Camera::lookAt(float x, float y, float z) {
}

void Camera::lookAt(ts::Vector::vec3 position) {
}

void Camera::move(ts::Vector::vec3 moveVector) {
	position += moveVector;
	viewMatrixNeedsUpdate = true;
}

void Camera::move(float dx, float dy, float dz) {
	position += ts::Vector::vec3(dx, dy, dz);
	viewMatrixNeedsUpdate = true;
}

void Camera::moveInDirection(ts::Vector::vec3 moveVector) {
	moveVector.z *= -1;
	ts::Vector::vec3 front, right, up;
	ts::Vector::quat temp = rotation;
	temp.w *= -1;
	ts::Vector::getQuaternionDirection(temp, front, right, up);
	position += front * moveVector.z;
	position += right * moveVector.x;
	position += up * moveVector.y;
	viewMatrixNeedsUpdate = true;
}

void Camera::moveInDirection(float dx, float dy, float dz) {
	moveInDirection(ts::Vector::vec3(dx, dy, dz));
}

void Camera::setPosition(ts::Vector::vec3 newPosition) {
	position = newPosition;
	viewMatrixNeedsUpdate = true;
}

void Camera::setPosition(float x, float y, float z) {
	position = ts::Vector::vec3(x, y, z);
	viewMatrixNeedsUpdate = true;
}

void Camera::setX(float x) {
	position.x = x;
	viewMatrixNeedsUpdate = true;
}

void Camera::setY(float y) {
	position.y = y;
	viewMatrixNeedsUpdate = true;
}

void Camera::setZ(float z) {
	position.z = z;
	viewMatrixNeedsUpdate = true;
}

ts::Vector::vec3 Camera::getPosition() {
	return position;
}

ts::Vector::mat4* Camera::getViewMatrix() {
	if(viewMatrixNeedsUpdate){
		viewMatrix = quaternionToMatrix(rotation) * translate(-position);
		viewMatrixNeedsUpdate = false;
	}

	return &viewMatrix;
}

} /* namespace ts */
