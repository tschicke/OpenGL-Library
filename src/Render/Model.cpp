/*
 * Model.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: Tyler
 */

#include "Model.h"

namespace ts {

Model::Model() {
	init(NULL/*default mesh*/, NULL/*defaultShader*/, glm::vec3(0, 0, 0), 0, 0);
}

Model::Model(Mesh* mesh, ShaderProgram* shaderProgram) {
	init(mesh, shaderProgram, glm::vec3(0, 0, 0), 0, 0);
}

Model::Model(Mesh* mesh, ShaderProgram* shaderProgram, glm::vec3 position, float yaw, float pitch) {
	init(mesh, shaderProgram, position, yaw, pitch);
}

void Model::init(Mesh * mesh, ShaderProgram * shaderProgram, glm::vec3 position, float yaw, float pitch) {
	this->mesh = mesh;
	this->shaderProgram = shaderProgram;
	this->position = position;
	this->yaw = yaw;
	this->pitch = pitch;
}

Model::~Model() {
}

void Model::translate(float x, float y, float z) {
	translate(glm::vec3(x, y, z));
}

void Model::translate(glm::vec3 translateVector) {
	position += translateVector;
}

void Model::setPosition(float x, float y, float z) {
	setPosition(glm::vec3(x, y, z));
}

void Model::setPosition(glm::vec3 position) {
	this->position = position;
}

glm::vec3 Model::getPosition() {
	return position;
}

void Model::rotateYaw(int deltaYaw) {
	yaw += deltaYaw;
	yaw %= 360;
}

void Model::rotatePitch(int deltaPitch) {
	pitch += deltaPitch;
	pitch = (pitch < -89 ? -89 : (pitch > 89 ? 89 : pitch));
}

void Model::setYaw(int yaw) {
	this->yaw = yaw;
	yaw %= 360;
}

void Model::setPitch(int pitch) {
	this->pitch = pitch;
	pitch = (pitch < -89 ? -89 : (pitch > 89 ? 89 : pitch));
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

void Model::draw(Camera* camera) {
	if(mesh == NULL || shaderProgram == NULL){
		return;
	}

	shaderProgram->useProgram();
	shaderProgram->setUniform("modelMatrix", &modelMatrix);
	shaderProgram->setUniform("viewMatrix", camera->getViewMatrix());
	shaderProgram->setUniform("projectionMatrix", );//TODO make projection matrix
}

} /* namespace ts */
