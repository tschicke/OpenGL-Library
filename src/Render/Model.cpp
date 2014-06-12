/*
 * Model.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: Tyler
 */

#include "Model.h"

#include "../Util/Camera.h"

#include "../Vector/MatrixTransform.h"
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

void Model::setMesh(Mesh* mesh) {
	this->mesh = mesh;
}

void Model::setShader(ShaderProgram* shaderProgram) {
	this->shaderProgram = shaderProgram;
}

void Model::setTexture(Texture* texture) {
	this->texture = texture;
}

void Model::draw(Camera* camera) {
	if (mesh == NULL || shaderProgram == NULL) {
		return;
	}
	if (modelMatrixNeedsUpdate) {
		modelMatrix = ts::Vector::translate(position) * ts::Vector::quaternionToMatrix(rotationQuaternion) ;
		modelMatrixNeedsUpdate = false;
	}

	if (texture != NULL) {
		texture->bindTexture();
	}

	ts::Vector::mat4 viewMatrix = *(camera->getViewMatrix());
	ts::Vector::mat4 projectionMatrix = *(ts::Window::getMainWindow()->getProjectionMatrix());

	ts::Vector::mat4 MVPMatrix = projectionMatrix * viewMatrix * modelMatrix;
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
