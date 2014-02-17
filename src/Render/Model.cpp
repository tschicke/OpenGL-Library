/*
 * Model.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: Tyler
 */

#include "Model.h"

#include <glm/gtx/transform.hpp>

#include "../Window/Window.h"

#include <iostream>

namespace ts {

Model::Model() {
	init(NULL/*default mesh*/, NULL/*defaultShader*/, NULL/*defaultTexture*/, glm::vec3(0, 0, 0), 0, 0);
}

Model::Model(Mesh* mesh, ShaderProgram* shaderProgram, Texture * texture) {
	init(mesh, shaderProgram, texture, glm::vec3(0, 0, 0), 0, 0);
}

Model::Model(Mesh* mesh, ShaderProgram* shaderProgram, Texture * texture, glm::vec3 position, float yaw, float pitch) {
	init(mesh, shaderProgram, texture, position, yaw, pitch);
}

void Model::init(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture, glm::vec3 position, float yaw, float pitch) {
	this->mesh = mesh;
	this->shaderProgram = shaderProgram;
	this->texture = texture;
	this->position = position;
	this->yaw = yaw;
	this->pitch = pitch;
	modelMatrixNeedsUpdate = true;
}

Model::~Model() {
}

void Model::translate(float x, float y, float z) {
	translate(glm::vec3(x, y, z));
}

void Model::translate(glm::vec3 translateVector) {
	position += translateVector;
	modelMatrixNeedsUpdate = true;
}

void Model::setPosition(float x, float y, float z) {
	setPosition(glm::vec3(x, y, z));
}

void Model::setPosition(glm::vec3 position) {
	this->position = position;
	modelMatrixNeedsUpdate = true;
}

glm::vec3 Model::getPosition() {
	return position;
}

void Model::rotateYaw(int deltaYaw) {
	yaw += deltaYaw;
	yaw %= 360;
	modelMatrixNeedsUpdate = true;
}

void Model::rotatePitch(int deltaPitch) {
	pitch += deltaPitch;
	pitch %= 360;
	modelMatrixNeedsUpdate = true;
}

void Model::setYaw(int yaw) {
	this->yaw = yaw;
	yaw %= 360;
	modelMatrixNeedsUpdate = true;
}

void Model::setPitch(int pitch) {
	this->pitch = pitch;
	pitch = (pitch < -89 ? -89 : (pitch > 89 ? 89 : pitch));
	modelMatrixNeedsUpdate = true;
}

int Model::getYaw() {
	return yaw;
}

int Model::getPitch() {
	return pitch;
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
	if(mesh == NULL || shaderProgram == NULL){
		return;
	}
	if(modelMatrixNeedsUpdate){
		modelMatrix = glm::translate(position) * glm::rotate((float) yaw, 0.f, 1.f, 0.f) * glm::rotate((float) pitch, 1.f, 0.f, 0.f);
		modelMatrixNeedsUpdate = false;
	}

	if(texture != NULL){
		texture->bindTexture();
	}

	glm::mat4 viewMatrix = *(camera->getViewMatrix());
	glm::mat4 projectionMatrix = *(ts::Window::getMainWindow()->getProjectionMatrix());

	glm::mat4 MVPMatrix = projectionMatrix * viewMatrix * modelMatrix;

	shaderProgram->useShaderProgram();
	shaderProgram->setUniform("MVPMatrix", &MVPMatrix);
//	shaderProgram->setUniform("modelMatrix", &modelMatrix);
//	shaderProgram->setUniform("viewMatrix", &viewMatrix);
//	shaderProgram->setUniform("projectionMatrix", &projectionMatrix);

	mesh->render();

	shaderProgram->disableShaderProgram();

	if(texture != NULL){
		texture->unbindTexture();
	}
}

} /* namespace ts */
