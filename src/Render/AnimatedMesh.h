/*
 * AnimatedMesh.h
 *
 *  Created on: May 21, 2014
 *      Author: tyler
 */

#ifndef ANIMATEDMESH_H_
#define ANIMATEDMESH_H_

#include <map>

#include "Mesh.h"
#include "../Vector/Vector.h"
#include "../Vector/Quaternion.h"
#include "../Vector/Matrix.h"

#include <string>

namespace ts {

struct Node {
public:
	int getNodeIndex();
	int getParentNodeIndex();

	Vector::vec3 getNodePosition();

	Vector::quat getNodeRotation();
	void rotateLocal(float angle, Vector::vec3 axis);
	void rotateGlobal(float angle, Vector::vec3 axis);
	void setRotationQuaternion(ts::Vector::quat quat);

	friend class ResourceManager;
private:
	int nodeIndex;
	int parentNodeIndex;

	Vector::vec3 position;
	Vector::quat rotationQuaternion;
};

struct Pose {
public:
	Pose();
	Pose(ts::Vector::quat * quaternionArray, int numBones);

	ts::Vector::quat * getQuatArray();
	int getNumBones();
private:
	ts::Vector::quat * quatArray;
	int numBones;
};

struct PoseLibrary {//TODO is this necessary?
public:
	Pose getPose(std::string poseName);

	friend class ResourceManager;
private:
	std::map<std::string, Pose *> poseMap;//TODO should be Pose * or Pose
};

class Skeleton {
public:
	Skeleton();

	Vector::mat4 * getMatrixArray();
	int getNumBones();

	void rotateBoneLocal(int nodeIndex, float angle, Vector::vec3 axis);
	void rotateBoneGlobal(int nodeIndex, float angle, Vector::vec3 axis);

	void setPose(Pose pose);

	Skeleton& operator =(const Skeleton& skeleton2);

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

	//TODO should a mesh have a default skeleton or should skeleton and mesh be separate?
	Skeleton * defaultSkeleton;//TODO Make pointers and make Skeleton Constructor private?
};

} /* namespace ts */
#endif /* ANIMATEDMESH_H_ */
