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

struct Node {
public:

private:
	Vector::vec3 position;
	Node * parentNode;
};

class Skeleton {
public:

	friend class ResourceManager;
private:
	Node * nodeArray;
};

class AnimatedMesh : public Mesh {
public:
	bool isAnimated();

	void render();
protected:
	AnimatedMesh();
	virtual ~AnimatedMesh();
};

} /* namespace ts */
#endif /* ANIMATEDMESH_H_ */
