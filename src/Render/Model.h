/*
 * Model.h
 *
 *  Created on: Nov 24, 2013
 *      Author: Tyler
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"

#include "../Vector/Vector.h"
#include "../Vector/Quaternion.h"
#include "../Vector/Matrix.h"

namespace ts {

class Camera;

class Model {
public:
	Model();
	Model(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture);
	Model(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture, ts::Vector::vec3 position);
	virtual ~Model();

	void translate(float x, float y, float z);
	void translate(ts::Vector::vec3 translateVector);
	void setPosition(float x, float y, float z);
	void setPosition(ts::Vector::vec3 position);
	ts::Vector::vec3 getPosition();

	void rotateGlobal(float angle, float axisX, float axisY, float axisZ);
	void rotateGlobal(float angle, ts::Vector::vec3 axis);
	void rotateLocal(float angle, float axisX, float axisY, float axisZ);
	void rotateLocal(float angle, ts::Vector::vec3 axis);
	void resetRotation();

	virtual void setMesh(Mesh * mesh);
	void setShader(ShaderProgram * shaderProgram);
	void setTexture(Texture * texture);

	virtual void draw(Camera * camera);

protected:
	Mesh * mesh;
	ShaderProgram * shaderProgram;
	Texture * texture;

	ts::Vector::mat4 modelMatrix;
	bool modelMatrixNeedsUpdate;

	ts::Vector::vec3 position;
	ts::Vector::quat rotationQuaternion;

	void init(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture, ts::Vector::vec3 position);
};

} /* namespace ts */
#endif /* MODEL_H_ */
