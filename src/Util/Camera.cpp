/*
 * Camera.cpp
 *
 *  Created on: Oct 26, 2013
 *      Author: Tyler
 */

#include "Camera.h"

#include "../Vector/MatrixTransform.h"
#include "../Vector/VectorOperations.h"

#include "MathHelper.h"

namespace ts {

Camera::Camera() {
	init(ts::Vector::vec3());
}

Camera::~Camera() {
}

Camera::Camera(ts::Vector::vec3 position) {
	init(position);
}

void Camera::init(ts::Vector::vec3 position) {
	yaw = 0;
	pitch = 0;
	this->position = position;
	lookDir = ts::Vector::vec3(0, 0, -1);
	upVector = ts::Vector::vec3(0, 1, 0);
	viewMatrixNeedsUpdate = true;
}

void Camera::move(ts::Vector::vec3 moveVector) {
	position += moveVector;
	viewMatrixNeedsUpdate = true;
}

void Camera::move(float dx, float dy, float dz) {
	move(ts::Vector::vec3(dx, dy, dz));
}

void Camera::moveInDirection(ts::Vector::vec3 moveVector) {
	float sinYaw = MathHelper::sin_float(MathHelper::toRadians(yaw));
	float cosYaw = MathHelper::cos_float(MathHelper::toRadians(yaw));

	float cameraDX = cosYaw * moveVector.x - sinYaw * moveVector.z;
	float cameraDY = moveVector.y;
	float cameraDZ = cosYaw * moveVector.z + sinYaw * moveVector.x;

	move(cameraDX, cameraDY, cameraDZ);
}

void Camera::moveInDirection(float dx, float dy, float dz) {
	moveInDirection(ts::Vector::vec3(dx, dy, dz));
}

void Camera::setPosition(ts::Vector::vec3 newPosition) {
	position = newPosition;
	viewMatrixNeedsUpdate = true;
}

void Camera::setPosition(float x, float y, float z) {
	setPosition(ts::Vector::vec3(x, y, z));
}

void Camera::setX(float x){
	this->position.x = x;
	viewMatrixNeedsUpdate = true;
}

void Camera::setY(float y){
	this->position.y = y;
	viewMatrixNeedsUpdate = true;
}

void Camera::setZ(float z){
	this->position.z = z;
	viewMatrixNeedsUpdate = true;
}

void Camera::addRoll(int add){
	roll += add;
	roll %= 360;
	viewMatrixNeedsUpdate = true;
}

ts::Vector::vec3 Camera::getPosition() {
	return position;
}

ts::Vector::vec3 Camera::getDirection() {
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

	lookDir = ts::Vector::vec3(lookDirX, lookDirY, lookDirZ);

	viewMatrixNeedsUpdate = true;
}

void Camera::lookAt(float x, float y, float z) {
	lookAt(ts::Vector::vec3(x, y, z));
}

void Camera::lookAt(ts::Vector::vec3 position) {
	lookDir = ts::Vector::normalize(position - this->position);
	viewMatrixNeedsUpdate = true;
}

ts::Vector::mat4 * Camera::getViewMatrix() {
	if (viewMatrixNeedsUpdate) {
		viewMatrix = ts::Vector::lookAt(position, position + lookDir, ts::Vector::vec3(0, 1, 0));
		viewMatrixNeedsUpdate = false;
	}
	return &viewMatrix;
}

} /* namespace ts */
