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

#include "../Vector/Vector.h"
#include "../Vector/Matrix.h"

namespace ts {

class Model {
public:
	Model();
	Model(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture);
	Model(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture, ts::Vector::vec3 position, float yaw, float pitch);
	virtual ~Model();

	void translate(float x, float y, float z);
	void translate(ts::Vector::vec3 translateVector);
	void setPosition(float x, float y, float z);
	void setPosition(ts::Vector::vec3 position);
	ts::Vector::vec3 getPosition();

	void rotateYaw(int deltaYaw);
	void rotatePitch(int deltaPitch);
	void setYaw(int yaw);
	void setPitch(int pitch);
	int getYaw();
	int getPitch();

	void scaleX(float scaleFactor);
	void scaleY(float scaleFactor);
	void scaleZ(float scaleFactor);
	void scale(ts::Vector::vec3 scaleVector);
	void setScaleX(float scaleX);
	void setScaleY(float scaleY);
	void setScaleZ(float scaleZ);
	void setScale(ts::Vector::vec3 scaleVector);
	ts::Vector::vec3 getScaleVector();

	void setMesh(Mesh * mesh);
	void setShader(ShaderProgram * shaderProgram);
	void setTexture(Texture * texture);

	void draw(Camera * camera);

private:
	Mesh * mesh;
	ShaderProgram * shaderProgram;
	Texture * texture;

	ts::Vector::mat4 modelMatrix;
	bool modelMatrixNeedsUpdate;

	ts::Vector::vec3 position;
	ts::Vector::vec3 scaleVector;
	int yaw, pitch;

	void init(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture, ts::Vector::vec3 position, float yaw, float pitch);
};

} /* namespace ts */
#endif /* MODEL_H_ */
