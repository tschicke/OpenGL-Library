/*
 * TestScene.cpp
 *
 *  Created on: Feb 11, 2014
 *      Author: Tyler
 */

#include "TestScene.h"

#include "Window.h"

#include "../Util/MathHelper.h"

#include <iostream>

#include "../Render/ResourceManager.h"

namespace ts {

TestScene::TestScene() {
	float vertexData1[] = {
			0, 0, 0,
			0, 0, 100,
			100, 0, 100,
			100, 0, 0,

			0, 0,
			5, 0,
			5, 5,
			0, 5,

			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
	};

	unsigned int indices1[] = {
			0, 1, 2,
			0, 2, 3
	};

	ResourceManager * manager = ResourceManager::getResourceManger();

	manager->loadMeshFromData("Square", vertexData1, indices1, 4, 6, true);
	manager->loadMeshFromFile("Monkey");
	manager->loadShaderProgram("textureShader", "textureShader");
	manager->loadTexture("BlockSheet");

	model = Model(manager->getMesh("Plane"), manager->getShaderProgram("textureShader", "textureShader"), manager->getTexture("MonkeyFaceTexture"));
	model.translate(0, 2, 0);
	model2 = Model(manager->getMesh("Sword2"), manager->getShaderProgram("textureShader", "textureShader"), manager->getTexture("MonkeyFaceTexture"));
	model2.translate(3, 2, 0);
	model2.rotateGlobal(45, ts::Vector::vec3(1, 0, 0));
	model2.rotateGlobal(45, ts::Vector::vec3(0, 1, 0));
	model2.rotateGlobal(-45, ts::Vector::vec3(1, 0, -1));
	plane = AnimatedModel(manager->getMesh("Terrain"), manager->getShaderProgram("textureShader", "textureShader"), manager->getTexture("Button1_default"));
//	plane.translate(-500, 0, -500);

	cameraSpeed = 0;
	camera.setPosition(camera.getPosition() + ts::Vector::vec3(0, 3, 0));
}

TestScene::~TestScene() {
}

void TestScene::update(time_t dt) {
	if (Keyboard::checkKeyEvent(Keyboard::Escape) == Keyboard::keyPressed) {
		Window::getMainWindow()->stop();
		return;
	}
	double secondScale = dt / 1000000.f;
	double fpsScale = 60.f * dt / 1000000.f;

	float cameraDZ = 0, cameraDY = 0, cameraDX = 0;
	float moveSpeed = 6.f;
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		cameraDZ += -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		cameraDZ += 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		cameraDY += -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::E)) {
		cameraDY += 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		cameraDX += -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		cameraDX += 1;
	}
	bool skip = false;
	if (Keyboard::checkKeyEvent(Keyboard::Space) == Keyboard::keyPressed) {
		cameraSpeed += 5;
		skip = true;
	}
	cameraDX *= moveSpeed * secondScale;
	cameraDY *= moveSpeed * secondScale;
	cameraDZ *= moveSpeed * secondScale;

	cameraSpeed -= 9.8f * secondScale;
	if (camera.getPosition().y + cameraDY < 10 && !skip) {
//		camera.setY(50);
		cameraSpeed = 0;
	}

	cameraDY += cameraSpeed;

	float lookSpeed = 1.f;
	float mouseDX = Mouse::getLastMove().x * lookSpeed;
	float mouseDY = Mouse::getLastMove().y * lookSpeed;

	camera.moveInDirection(cameraDX, cameraDY, cameraDZ);
	if (Mouse::isMouseButtonPressed(Mouse::Button0)) {
		camera.rotateLocal(-mouseDY, 1, 0, 0);
		camera.rotateGlobal(mouseDX, 0, 1, 0);
	}

	float modelYaw = 0;
	float modelPitch = 0;

	if (ts::Keyboard::isKeyPressed(ts::Keyboard::Up)) {
		modelPitch++;
	} else if (ts::Keyboard::isKeyPressed(ts::Keyboard::Down)) {
		modelPitch--;
	}
	if (ts::Keyboard::isKeyPressed(ts::Keyboard::Left)) {
		modelYaw--;
	} else if (ts::Keyboard::isKeyPressed(ts::Keyboard::Right)) {
		modelYaw++;
	}

	camera.rotateLocal(modelYaw, 0, 0, 1);
	camera.rotateLocal(modelPitch, 1, 0, 0);
	model.rotateLocal(modelYaw, ts::Vector::vec3(0, 0, 1));
	model.rotateLocal(modelPitch, ts::Vector::vec3(1, 0, 0));
}

void TestScene::draw() {
	model.draw(&camera);
	model2.draw(&camera);
	plane.draw(&camera);
}

} /* namespace ts */
