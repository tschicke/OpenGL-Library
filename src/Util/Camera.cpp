/*
 * Camera.cpp
 *
 *  Created on: Oct 26, 2013
 *      Author: Tyler
 */

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "MathHelper.h"

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
	viewMatrixNeedsUpdate = true;
}

void Camera::move(float dx, float dy, float dz) {
	move(glm::vec3(dx, dy, dz));
}

void Camera::moveInDirection(glm::vec3 moveVector) {
	float cameraDX = 0;
	float cameraDY = 0;
	float cameraDZ = 0;
	//TODO finish this
}

void Camera::moveInDirection(float dx, float dy, float dz) {
	moveInDirection(glm::vec3(dx, dy, dz));
}

void Camera::setPosition(glm::vec3 newPosition) {
	position = newPosition;
	viewMatrixNeedsUpdate = true;
}

void Camera::setPosition(int x, int y, int z) {
	setPosition(glm::vec3(x, y, z));
}

glm::vec3 Camera::getPosition() {
	return position;
}

glm::vec3 Camera::getDirection() {
	return lookDir;
}

// Positive dx = counter-clockwise/left rotation
void Camera::rotate(int dx, int dy) {
	yaw += dx;
	yaw %= 360;
	pitch += dy;
	pitch = (pitch < -89 ? -89 : (pitch > 89 ? 89 : pitch));

	float lookDirX = MathHelper::cos_float(MathHelper::toRadians(pitch)) * MathHelper::sin_float(MathHelper::toRadians(yaw));
	float lookDirY = MathHelper::sin_float(MathHelper::toRadians(pitch));
	float lookDirZ = MathHelper::cos_float(MathHelper::toRadians(pitch)) * -MathHelper::cos_float(MathHelper::toRadians(yaw));

	lookDir = glm::vec3(lookDirX, lookDirY, lookDirZ);

	viewMatrixNeedsUpdate = true;
}

glm::mat4 * Camera::getViewMatrix() {
	if (viewMatrixNeedsUpdate) {
		viewMatrix = glm::lookAt(position, position + lookDir, glm::vec3(0, 1, 0));
		viewMatrixNeedsUpdate = false;
	}
	return &viewMatrix;
}

} /* namespace ts */
