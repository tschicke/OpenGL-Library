/*
 * Mesh.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: Tyler
 */

#include "Mesh.h"

#include <gl/glew.h>
#include <gl/gl.h>

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

bool Mesh::loadMeshFromOBJ(const char* objPath) {
	textured = true;
}

bool Mesh::loadMeshFromData(float* vertexData, int numVertices, unsigned int* indices, int numIndices, bool textured) {
	this->textured = textured;
	this->numVertices = numVertices;
	this->numIndices = numIndices;

	glGenBuffers(1, &vertexID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices, vertexData, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * numIndices, indices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}

void Mesh::render() {
	if (vertexID == -1 || indexID == -1) {
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

	glDrawArrays(GL_TRIANGLES, 0, numIndices);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

} /* namespace ts */
