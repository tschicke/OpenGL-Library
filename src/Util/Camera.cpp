/*
 * Camera.cpp
 *
 *  Created on: Oct 26, 2013
 *      Author: Tyler
 */

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace ts {

Camera::Camera() {
	init(glm::vec3());
}

Camera::~Camera() {
}

Camera::Camera(glm::vec3 position) {
	init(position);
}

void Camera::init(glm::vec3 position) {
	yaw = 0;
	pitch = 0;
	this->position = position;
	lookDir = glm::vec3(0, 0, -1);
	viewMatrixNeedsUpdate = true;
}

void Camera::move(glm::vec3 moveVector) {
	position += moveVector;
}

void Camera::move(float dx, float dy, float dz) {
	position += glm::vec3(dx, dy, dz);
}

void Camera::setPosition(glm::vec3 newPosition) {
	position = newPosition;
}

void Camera::setPosition(int x, int y, int z) {
	position = glm::vec3(x, y, z);
}

glm::vec3 Camera::getPosition() {
	return position;
}

glm::vec3 Camera::getDirection() {
	return lookDir;
}

void Camera::rotate(int dx, int dy) {
	yaw += dx;
	yaw = (yaw < 0 ? 0 : (yaw > 360 ? 360 : yaw));
	pitch += dy;
	pitch = (pitch < -180 ? -180 : (pitch > 180 ? 180 : pitch));
}

glm::mat4 Camera::getViewMatrix() {
	if (viewMatrixNeedsUpdate) {
		viewMatrix = glm::lookAt(position, position + lookDir, glm::vec3(0, 1, 0));
		viewMatrixNeedsUpdate = false;
	}
	return viewMatrix;
}

} /* namespace ts */
