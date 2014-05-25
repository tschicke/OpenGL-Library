/*
 * AnimatedMesh.h
 *
 *  Created on: May 21, 2014
 *      Author: tyler
 */

#ifndef ANIMATEDMESH_H_
#define ANIMATEDMESH_H_

#include "Mesh.h"
#include "../Vector/Vector.h"

namespace ts {

class AnimatedMesh : public Mesh{
public:
	bool isAnimated();

	void render();

	int getNumBones();
	Vector::vec3 * getDefaultBonePositions();
protected:
	AnimatedMesh();
	virtual ~AnimatedMesh();

	Vector::vec3 * defaultBonePositions;
	int numBones;
};

} /* namespace ts */
#endif /* ANIMATEDMESH_H_ */
