/*
 * Model.h
 *
 *  Created on: Nov 24, 2013
 *      Author: Tyler
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "../Util/Camera.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include <glm/glm.hpp>

namespace ts {

class Model {
public:
	Model();
	Model(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture);
	Model(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture, glm::vec3 position, float yaw, float pitch);
	virtual ~Model();

	void translate(float x, float y, float z);
	void translate(glm::vec3 translateVector);
	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();

	void rotateYaw(int deltaYaw);
	void rotatePitch(int deltaPitch);
	void setYaw(int yaw);
	void setPitch(int pitch);
	int getYaw();
	int getPitch();

	void scaleX(float scaleFactor);
	void scaleY(float scaleFactor);
	void scaleZ(float scaleFactor);
	void scale(glm::vec3 scaleVector);
	void setScaleX(float scaleX);
	void setScaleY(float scaleY);
	void setScaleZ(float scaleZ);
	void setScale(glm::vec3 scaleVector);
	glm::vec3 getScaleVector();

	void setMesh(Mesh * mesh);
	void setShader(ShaderProgram * shaderProgram);
	void setTexture(Texture * texture);

	void draw(Camera * camera);

private:
	Mesh * mesh;
	ShaderProgram * shaderProgram;
	Texture * texture;

	glm::mat4 modelMatrix;
	bool modelMatrixNeedsUpdate;

	glm::vec3 position;
	glm::vec3 scaleVector;
	int yaw, pitch;

	void init(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture, glm::vec3 position, float yaw, float pitch);
};

} /* namespace ts */
#endif /* MODEL_H_ */
