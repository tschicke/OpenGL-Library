/*
 * Mesh.h
 *
 *  Created on: Nov 8, 2013
 *      Author: Tyler
 */

#ifndef MESH_H_
#define MESH_H_

#include <glm/glm.hpp>
#include <vector>

namespace ts {

class Mesh {
public:
	Mesh();
	virtual ~Mesh();

	void render();

protected:
	int vertexID, indexID;
	int numVertices, numIndices;
};

} /* namespace ts */
#endif /* MESH_H_ */
