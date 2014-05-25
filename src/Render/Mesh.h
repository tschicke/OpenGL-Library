/*
 * Mesh.h
 *
 *  Created on: Nov 8, 2013
 *      Author: Tyler
 */

#ifndef MESH_H_
#define MESH_H_

namespace ts {

class Mesh {
public:
	virtual bool isAnimated();

	virtual void render();

	friend class ResourceManager;
protected:
	Mesh();
	virtual ~Mesh();

	unsigned int vertexID, indexID;
	int numVertices, numIndices;

	bool textured;
};

} /* namespace ts */
#endif /* MESH_H_ */
