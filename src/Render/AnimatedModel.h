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

class AnimatedModel : public Model {
public:
	AnimatedModel();
	using Model::Model;//TODO Should use "using" or declare each constructor individually?
	virtual ~AnimatedModel();

	void rotateBoneLocal(int boneIndex, float angle, Vector::vec3 axis);
	void rotateBoneGlobal(int boneIndex, float angle, Vector::vec3 axis);

	void draw(Camera * camera);
protected:
	Skeleton skeleton;
};

} /* namespace ts */
#endif /* ANIMATEDMODEL_H_ */
