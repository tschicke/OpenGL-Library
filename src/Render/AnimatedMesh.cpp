/*
 * AnimatedMesh.cpp
 *
 *  Created on: May 21, 2014
 *      Author: tyler
 */

#include "AnimatedMesh.h"

#include <assert.h>

#include "../Vector/QuaternionOperations.h"
#include "../Vector/MatrixTransform.h"

#ifdef _WIN32
#include <gl/glew.h>
#elif defined __linux__
#include <GL/glew.h>
#endif

namespace ts {

//Node functions
int Node::getNodeIndex(){
	return nodeIndex;
}

int Node::getParentNodeIndex(){
	return parentNodeIndex;
}

Vector::vec3 Node::getNodePosition(){
	return position;
}

Vector::quat Node::getNodeRotation(){
	return rotationQuaternion;
}

void Node::rotateLocal(float angle, Vector::vec3 axis){
	rotationQuaternion = rotationQuaternion * Vector::angleAxisToQuaternion(angle, axis);
}

void Node::rotateGlobal(float angle, Vector::vec3 axis){
	rotationQuaternion = Vector::angleAxisToQuaternion(angle, axis) * rotationQuaternion;
}

//Skeleton Functions
Vector::mat4 * Skeleton::getMatrixArray(){
	for(int i = 0; i < numBones; ++i){
		Node node = boneArray[i];
		while(node.getParentNodeIndex() != -1){
			modelMatrixArray[i] = modelMatrixArray[i] * Vector::translate(node.getNodePosition()) * Vector::quaternionToMatrix(node.getNodeRotation());
			node = boneArray[node.getParentNodeIndex()];
		}
	}

	return modelMatrixArray;
}

int Skeleton::getNumBones(){
	return numBones;
}

void Skeleton::rotateBoneLocal(int boneIndex, float angle, Vector::vec3 axis){
	assert(boneIndex < numBones);
	boneArray[boneIndex].rotateLocal(angle, axis);
}

void Skeleton::rotateBoneGlobal(int boneIndex, float angle, Vector::vec3 axis){
	assert(boneIndex < numBones);
	boneArray[boneIndex].rotateGlobal(angle, axis);
}

//AnimatedMesh Functions
AnimatedMesh::AnimatedMesh() {
}

AnimatedMesh::~AnimatedMesh() {
}

bool AnimatedMesh::isAnimated() {
	return true;
}

Skeleton AnimatedMesh::getDefaultSkeleton(){
	return defaultSkeleton;
}

void AnimatedMesh::render() {
	if (vertexID == (unsigned int) (-1) || indexID == (unsigned int) (-1)) {
		return;
	}

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, vertexID);

	int vertexSize = 3;
	int textureSize = (textured ? 2 : 3);
	int normalSize = 3;
	int boneIndexSize = 2;
	int boneWeightSize = 2;

	//Vertex
	glVertexAttribPointer(0, vertexSize, GL_FLOAT, GL_FALSE, 0, (void *) 0);
	//Texture
	glVertexAttribPointer(1, textureSize, GL_FLOAT, GL_FALSE, 0, (void *) (vertexSize * sizeof(float) * numVertices));
	//Normal
	glVertexAttribPointer(2, normalSize, GL_FLOAT, GL_FALSE, 0, (void *) ((vertexSize + textureSize) * sizeof(float) * numVertices));
	//Bone Index
	glVertexAttribPointer(3, boneIndexSize, GL_UNSIGNED_BYTE, GL_FALSE, 0, (void *) ((vertexSize + textureSize + normalSize) * sizeof(float) * numVertices));
	//Bone Weights
	glVertexAttribPointer(4, boneWeightSize, GL_FLOAT, GL_FALSE, 0, (void *) ((((vertexSize + textureSize + normalSize) * sizeof(float)) + (boneIndexSize * sizeof(unsigned char))) * numVertices));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);

	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (void *) 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
}

} /* namespace ts */