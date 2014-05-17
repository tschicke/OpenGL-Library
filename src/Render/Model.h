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

	void rotate(float angle, float axisX, float axisY, float axisZ);
	void rotate(float angle, ts::Vector::vec3 axis);
	void resetRotation();


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
	ts::Vector::quat rotationQuaternion;

	void init(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture, ts::Vector::vec3 position);
};

} /* namespace ts */
#endif /* MODEL_H_ */
