/*
 * AnimatedModel.h
 *
 *  Created on: May 21, 2014
 *      Author: tyler
 */

#ifndef ANIMATEDMODEL_H_
#define ANIMATEDMODEL_H_

#include "Model.h"

#include "AnimatedMesh.h"

namespace ts {

class AnimatedModel: public Model {
public:
	AnimatedModel();
	AnimatedModel(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture);
	AnimatedModel(Mesh * mesh, ShaderProgram * shaderProgram, Texture * texture, ts::Vector::vec3 position);
	virtual ~AnimatedModel();

	void setMesh(Mesh * mesh);

	void rotateBoneLocal(int boneIndex, float angle, Vector::vec3 axis);
	void rotateBoneGlobal(int boneIndex, float angle, Vector::vec3 axis);

	int getNumBones();

	void setPose(Pose pose);//TODO Should be pointer?
	void resetSkeleton();//TODO make default pose in skeleton and use that to reset it

	void draw(Camera * camera);
	protected:
	Skeleton skeleton;
};

} /* namespace ts */
#endif /* ANIMATEDMODEL_H_ */
