/*
 * Mesh.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: Tyler
 */

#include "Mesh.h"

#ifdef _WIN32
#include <gl/glew.h>
#elif defined __linux__
#include <GL/glew.h>
#endif

namespace ts {

Mesh::Mesh() {
	vertexID = -1;
	indexID = -1;
	numVertices = 0;
	numIndices = 0;
	textured = false;
}

Mesh::~Mesh() {
}

bool Mesh::isAnimated(){
	return false;
}

void Mesh::render() {
	if (vertexID == (unsigned int) -1 || indexID == (unsigned int) -1) {
		return;
	}

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexID);

	int vertexSize = 3;
	int textureSize = (textured ? 2 : 3);
	int normalSize = 3;

	//Vertex
	glVertexAttribPointer(0, vertexSize, GL_FLOAT, GL_FALSE, 0, (void *) 0);
	//Texture
	glVertexAttribPointer(1, textureSize, GL_FLOAT, GL_FALSE, 0, (void *) (vertexSize * sizeof(float) * numVertices));
	//Normal
	glVertexAttribPointer(2, normalSize, GL_FLOAT, GL_FALSE, 0, (void *) ((vertexSize + textureSize) * sizeof(float) * numVertices));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);

	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (void *) 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

} /* namespace ts */
