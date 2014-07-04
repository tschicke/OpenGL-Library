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
#include "../Vector/Quaternion.h"
#include "../Vector/Matrix.h"

namespace ts {

struct Node {
public:
	int getNodeIndex();
	int getParentNodeIndex();

	Vector::vec3 getNodePosition();

	Vector::quat getNodeRotation();
	void rotateLocal(float angle, Vector::vec3 axis);
	void rotateGlobal(float angle, Vector::vec3 axis);

	friend class ResourceManager;
private:
	int nodeIndex;
	int parentNodeIndex;

	Vector::vec3 position;
	Vector::quat rotationQuaternion;
};

class Skeleton {
public:
	Skeleton();

	Vector::mat4 * getMatrixArray();
	int getNumBones();

	void rotateBoneLocal(int nodeIndex, float angle, Vector::vec3 axis);
	void rotateBoneGlobal(int nodeIndex, float angle, Vector::vec3 axis);

	friend class ResourceManager;

private:
	int numBones;
	Node * boneArray;
	Vector::mat4 * modelMatrixArray;

	bool matrixArrayNeedsUpdate;
};

class AnimatedMesh : public Mesh {
public:
	bool isAnimated();

	Skeleton getDefaultSkeleton();

	void render();

	friend class ResourceManager;
protected:
	AnimatedMesh();
	virtual ~AnimatedMesh();

	Skeleton * defaultSkeleton;//TODO Make pointers and make Skeleton Constructor private?
};

} /* namespace ts */
#endif /* ANIMATEDMESH_H_ */
