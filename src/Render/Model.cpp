/*
 * Model.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: Tyler
 */

#include "Model.h"

#include "../Util/OldCamera.h"

#include "../Vector/MatrixTransform.h"
#include "../Vector/Quaternion.h"
#include "../Vector/QuaternionOperations.h"

#include "../Window/Window.h"

#include <iostream>

#include "../Util/MathHelper.h"

namespace ts {

Model::Model() {
	init(NULL/*default mesh*/, NULL/*defaultShader*/, NULL/*defaultTexture*/, ts::Vector::vec3(0, 0, 0));
}

Model::Model(Mesh* mesh, ShaderProgram* shaderProgram, Texture * texture) {
	init(mesh, shaderProgram, texture, ts::Vector::vec3(0, 0, 0));
}

Model::Model(Mesh* mesh, ShaderProgram* shaderProgram, Texture * texture, ts::Vector::vec3 position) {
	init(mesh, shaderProgram, texture, position);
}

void Model::init(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture, ts::Vector::vec3 position) {
	this->mesh = mesh;
	this->shaderProgram = shaderProgram;
	this->texture = texture;
	this->position = position;
	this->scaleVector = ts::Vector::vec3(1, 1, 1);
	this->rotationQuaternion = ts::Vector::quat(1, 0, 0, 0); //TODO add rotation initializer in constructor
	modelMatrixNeedsUpdate = true;
}

Model::~Model() {
}

void Model::translate(float x, float y, float z) {
	translate(ts::Vector::vec3(x, y, z));
}

void Model::translate(ts::Vector::vec3 translateVector) {
	position += translateVector;
	modelMatrixNeedsUpdate = true;
}

void Model::setPosition(float x, float y, float z) {
	setPosition(ts::Vector::vec3(x, y, z));
}

void Model::setPosition(ts::Vector::vec3 position) {
	this->position = position;
	modelMatrixNeedsUpdate = true;
}

ts::Vector::vec3 Model::getPosition() {
	return position;
}

void Model::rotateGlobal(float angle, float axisX, float axisY, float axisZ) {
	rotateGlobal(angle, ts::Vector::vec3(axisX, axisY, axisZ));
}

void Model::rotateGlobal(float angle, ts::Vector::vec3 axis) {
	rotationQuaternion = ts::Vector::angleAxisToQuaternion(angle, axis) * rotationQuaternion;
	modelMatrixNeedsUpdate = true;
}

void Model::rotateLocal(float angle, float axisX, float axisY, float axisZ) {
	rotateLocal(angle, ts::Vector::vec3(axisX, axisY, axisZ));
}

void Model::rotateLocal(float angle, ts::Vector::vec3 axis) {
	rotationQuaternion = rotationQuaternion * ts::Vector::angleAxisToQuaternion(angle, axis);
	modelMatrixNeedsUpdate = true;
}

void Model::resetRotation() {
	rotationQuaternion = ts::Vector::quat(1, 0, 0, 0);
	modelMatrixNeedsUpdate = true;
}

void Model::scaleX(float scaleFactor) {
	scaleVector.x *= scaleFactor;
	modelMatrixNeedsUpdate = true;
}

void Model::scaleY(float scaleFactor) {
	scaleVector.y *= scaleFactor;
	modelMatrixNeedsUpdate = true;
}

void Model::scaleZ(float scaleFactor) {
	scaleVector.z *= scaleFactor;
	modelMatrixNeedsUpdate = true;
}

void Model::scale(ts::Vector::vec3 scaleVector) {
	this->scaleVector.x *= scaleVector.x;
	this->scaleVector.y *= scaleVector.y;
	this->scaleVector.z *= scaleVector.z;
	modelMatrixNeedsUpdate = true;
}

void Model::setScaleX(float scaleX) {
	scaleVector.x = scaleX;
	modelMatrixNeedsUpdate = true;
}

void Model::setScaleY(float scaleY) {
	scaleVector.y = scaleY;
	modelMatrixNeedsUpdate = true;
}

void Model::setScaleZ(float scaleZ) {
	scaleVector.z = scaleZ;
	modelMatrixNeedsUpdate = true;
}

void Model::setScale(ts::Vector::vec3 scaleVector) {
	this->scaleVector = scaleVector;
	modelMatrixNeedsUpdate = true;
}

ts::Vector::vec3 Model::getScaleVector() {
	return scaleVector;
}

void Model::setMesh(Mesh* mesh) {
	this->mesh = mesh;
}

void Model::setShader(ShaderProgram* shaderProgram) {
	this->shaderProgram = shaderProgram;
}

void Model::setTexture(Texture* texture) {
	this->texture = texture;
}

void Model::draw(OldCamera* camera) {
	if (mesh == NULL || shaderProgram == NULL) {
		return;
	}
	if (modelMatrixNeedsUpdate) {
		modelMatrix = ts::Vector::translate(position) * ts::Vector::quaternionToMatrix(rotationQuaternion) * ts::Vector::scale(scaleVector);
		modelMatrixNeedsUpdate = false;
	}

	if (texture != NULL) {
		texture->bindTexture();
	}

	ts::Vector::mat4 viewMatrix = *(camera->getViewMatrix());
	ts::Vector::mat4 projectionMatrix = *(ts::Window::getMainWindow()->getProjectionMatrix());

	ts::Vector::mat4 MVPMatrix = projectionMatrix * viewMatrix * modelMatrix;
//	ts::Vector::mat4 NormalMatrix = ts::Vector::transpose(ts::Vector::inverse(modelMatrix));
	ts::Vector::mat4 NormalMatrix = ts::Vector::mat4(1);

	shaderProgram->useShaderProgram();
	shaderProgram->setUniform("MVPMatrix", &MVPMatrix);
	shaderProgram->setUniform("NormalMatrix", &NormalMatrix);
//	shaderProgram->setUniform("ModelMatrix", &modelMatrix);
//	shaderProgram->setUniform("ViewMatrix", &viewMatrix);
//	shaderProgram->setUniform("ProjectionMatrix", &projectionMatrix);

	mesh->render();

	shaderProgram->disableShaderProgram();

	if (texture != NULL) {
		texture->unbindTexture();
	}
}

} /* namespace ts */
