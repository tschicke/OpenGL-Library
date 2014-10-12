/*
 * AnimatedModel.cpp
 *
 *  Created on: May 21, 2014
 *      Author: tyler
 */

#include "AnimatedModel.h"

#include "../Util/Camera.h"

#include "../Window/Window.h"

#include "../Vector/MatrixTransform.h"
#include "../Vector/QuaternionOperations.h"

#include <iostream>

namespace ts {

AnimatedModel::AnimatedModel() {
}

AnimatedModel::AnimatedModel(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture)
:
		Model(mesh, shaderProgram, texture) {
	if (mesh->isAnimated()) {
		skeleton = ((AnimatedMesh *) mesh)->getDefaultSkeleton();
	}
}

AnimatedModel::AnimatedModel(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture, ts::Vector::vec3 position)
:
		Model(mesh, shaderProgram, texture, position) {
	if (mesh->isAnimated()) {
		skeleton = ((AnimatedMesh *) mesh)->getDefaultSkeleton();
	}
}

AnimatedModel::~AnimatedModel() {
}

void AnimatedModel::setMesh(Mesh * mesh) {
	Model::setMesh(mesh);
	if (mesh->isAnimated()) {
		skeleton = ((AnimatedMesh *) mesh)->getDefaultSkeleton();
	}
}

void AnimatedModel::rotateBoneLocal(int boneIndex, float angle, Vector::vec3 axis) {
	if (mesh == NULL || !mesh->isAnimated())
		return;
	skeleton.rotateBoneLocal(boneIndex, angle, axis);
}

void AnimatedModel::rotateBoneGlobal(int boneIndex, float angle, Vector::vec3 axis) {
	if (mesh == NULL || !mesh->isAnimated())
		return;
	skeleton.rotateBoneGlobal(boneIndex, angle, axis);
}

int AnimatedModel::getNumBones() {
	return skeleton.getNumBones();
}

void AnimatedModel::setPose(Pose pose){
	skeleton.setPose(pose);
}

void AnimatedModel::resetSkeleton() {
	if (mesh == NULL) {
		return;
	}
	if (!mesh->isAnimated()) {
		return;
	}
	skeleton = ((AnimatedMesh *) mesh)->getDefaultSkeleton();
}

void AnimatedModel::draw(Camera * camera) {
	if (mesh == NULL || shaderProgram == NULL) {
		return;
	}
	if (modelMatrixNeedsUpdate) {
		modelMatrix = ts::Vector::translate(position) * ts::Vector::quaternionToMatrix(rotationQuaternion);
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
	if (mesh->isAnimated()) {
		ts::Vector::mat4 * bones = skeleton.getMatrixArray();
//		for(int i = 0; i < skeleton.getNumBones(); ++i){
//			bones[i].print();
//		}
		shaderProgram->setUniform("Bones", bones, skeleton.getNumBones());
	}
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
