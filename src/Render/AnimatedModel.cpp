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

namespace ts {

AnimatedModel::AnimatedModel() {
}

AnimatedModel::~AnimatedModel() {
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

	ts::Vector::mat4 * bones = skeleton.getMatrixArray();

	shaderProgram->useShaderProgram();
	shaderProgram->setUniform("MVPMatrix", &MVPMatrix);
	shaderProgram->setUniform("Bones", bones);
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
