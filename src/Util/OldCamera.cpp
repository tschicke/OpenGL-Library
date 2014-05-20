/*
 * Camera.cpp
 *
 *  Created on: Oct 26, 2013
 *      Author: Tyler
 */

#include "OldCamera.h"

#include "../Vector/MatrixTransform.h"
#include "../Vector/VectorOperations.h"

#include "MathHelper.h"

namespace ts {

OldCamera::OldCamera() {
	init(ts::Vector::vec3());
}

OldCamera::~OldCamera() {
}

OldCamera::OldCamera(ts::Vector::vec3 position) {
	init(position);
}

void OldCamera::init(ts::Vector::vec3 position) {
	yaw = 0;
	pitch = 0;
	this->position = position;
	lookDir = ts::Vector::vec3(0, 0, -1);
	upVector = ts::Vector::vec3(0, 1, 0);
	viewMatrixNeedsUpdate = true;
}

void OldCamera::move(ts::Vector::vec3 moveVector) {
	position += moveVector;
	viewMatrixNeedsUpdate = true;
}

void OldCamera::move(float dx, float dy, float dz) {
	move(ts::Vector::vec3(dx, dy, dz));
}

void OldCamera::moveInDirection(ts::Vector::vec3 moveVector) {
	float sinYaw = MathHelper::sin_float(MathHelper::toRadians(yaw));
	float cosYaw = MathHelper::cos_float(MathHelper::toRadians(yaw));

	float cameraDX = cosYaw * moveVector.x - sinYaw * moveVector.z;
	float cameraDY = moveVector.y;
	float cameraDZ = cosYaw * moveVector.z + sinYaw * moveVector.x;

	move(cameraDX, cameraDY, cameraDZ);
}

void OldCamera::moveInDirection(float dx, float dy, float dz) {
	moveInDirection(ts::Vector::vec3(dx, dy, dz));
}

void OldCamera::setPosition(ts::Vector::vec3 newPosition) {
	position = newPosition;
	viewMatrixNeedsUpdate = true;
}

void OldCamera::setPosition(float x, float y, float z) {
	setPosition(ts::Vector::vec3(x, y, z));
}

void OldCamera::setX(float x){
	this->position.x = x;
	viewMatrixNeedsUpdate = true;
}

void OldCamera::setY(float y){
	this->position.y = y;
	viewMatrixNeedsUpdate = true;
}

void OldCamera::setZ(float z){
	this->position.z = z;
	viewMatrixNeedsUpdate = true;
}

ts::Vector::vec3 OldCamera::getPosition() {
	return position;
}

ts::Vector::vec3 OldCamera::getDirection() {
	return lookDir;
}

// Positive dx = counter-clockwise/left rotation
void OldCamera::rotate(int dx, int dy) {
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

void OldCamera::lookAt(float x, float y, float z) {
	lookAt(ts::Vector::vec3(x, y, z));
}

void OldCamera::lookAt(ts::Vector::vec3 position) {
	lookDir = ts::Vector::normalize(position - this->position);
	viewMatrixNeedsUpdate = true;
}

ts::Vector::mat4 * OldCamera::getViewMatrix() {
	if (viewMatrixNeedsUpdate) {
		viewMatrix = ts::Vector::lookAt(position, position + lookDir, upVector);
		viewMatrixNeedsUpdate = false;
	}
	return &viewMatrix;
}

} /* namespace ts */
