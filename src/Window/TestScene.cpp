/*
 * TestScene.cpp
 *
 *  Created on: Feb 11, 2014
 *      Author: Tyler
 */

#include "TestScene.h"

#include <iostream>

#include "../Render/ResourceManager.h"

namespace ts {

TestScene::TestScene() {
	camera.setPosition(0, 0, 2);

	float vertexData[] = { 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0,

	0, 0, 1, 0, 1, 1, 0, 1,

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

	unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };

	ResourceManager * manager = ResourceManager::getResourceManger();

	manager->loadMeshFromData("Square", vertexData, indices, 4, 6, true);
	manager->loadShaderProgram("textureShader", "textureShader");
	manager->loadTexture("Button1_default");

	model = Model(manager->getMesh("Square"), manager->getShaderProgram("textureShader", "textureShader"));
	model.setTexture(manager->getTexture("Button1_default"));
}

TestScene::~TestScene() {
}

void TestScene::update(time_t dt) {
	float scale = 60.f * dt / 1000000.f;

//	model.rotateYaw(1);
	model.rotatePitch(1);

	float cameraDZ = 0, cameraDX = 0;
	float moveSpeed = 6.f / 60.f;
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		cameraDZ += -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		cameraDZ += 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		cameraDX += -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		cameraDX += 1;
	}
	cameraDX *= moveSpeed * scale;
	cameraDZ *= moveSpeed * scale;

	float lookSpeed = 1.f;
	float mouseDX = Mouse::getLastMove().x * lookSpeed * scale;
	float mouseDY = Mouse::getLastMove().y * lookSpeed * scale;

	std::cout << Mouse::getLastMove().x << ' ' << Mouse::getLastMove().y << '\n';

	camera.move(cameraDX, 0, cameraDZ);
	camera.rotate(mouseDX, mouseDY);
}

void TestScene::draw() {
	model.draw(&camera);
}

} /* namespace ts */
