/*
 * ResourceManager.h
 *
 *  Created on: Jan 22, 2014
 *      Author: Tyler
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <map>
#include <string>

#include "Mesh.h"
#include "AnimatedMesh.h"
#include "ShaderProgram.h"
#include "Texture.h"

namespace ts {

class ResourceManager {
public:
	static ResourceManager * getResourceManger();

	bool loadMeshFromFile(std::string meshName);
	bool loadMeshFromData(std::string meshName, float * vertexData, unsigned int * indexData, int numVertices, int numIndices, bool textured);
	bool loadAnimatedMeshFromFile(std::string animatedMeshName);
	bool loadAnimatedMeshFromData(std::string animatedMeshName, float * vertexData, float * boneData, unsigned int * indexData, int numVertices, int numIndices, int numBones, bool textured);
	bool loadShaderProgram(std::string vertexShaderName, std::string fragmentShaderName);
	bool loadTexture(std::string textureName);
	bool loadPoseLibrary(std::string poseLibraryName);

	bool modifyMeshVertexData(std::string meshName, float * vertexData, int numVertices, int vertexOffset);
	//TODO add modify animated mesh
	bool modifyMeshTextureData(std::string meshName, float * textureData, int numUVs, int textureOffset);
	bool modifyMeshNormalData(std::string meshName, float * normalData, int numNormals, int normalOffset);
	bool modifyMeshIndexData(std::string meshName, unsigned int * indexData, int numIndices, int indexOffset);

	Mesh * getMesh(std::string meshName);
	AnimatedMesh * getAnimatedMesh(std::string animatedMeshName);
	ShaderProgram * getShaderProgram(std::string vertexShaderName, std::string fragmentShaderName);
	Texture * getTexture(std::string textureName);
	PoseLibrary * getPoseLibrary(std::string poseLibraryName);

	void deleteMesh(std::string meshName);
	void deleteAnimatedMesh(std::string animatedMeshName);//TODO implement
	void deleteShaderProgram(std::string shaderProgramName);
	void deleteTexture(std::string textureName);
	//TODO add deletePoseLibrary

	void cleanupMeshes();
	void cleanupAnimatedMeshes();//TODO implement
	void cleanupShaderPrograms();
	void cleanupTextures();
	//TODO add cleanupPoseLibrary

	void cleanupAll();

private:
	ResourceManager();
	virtual ~ResourceManager();

	static ResourceManager resourceManager;

	std::map<std::string, Mesh *> meshMap;
	std::map<std::string, AnimatedMesh *> animatedMeshMap;
	std::map<std::string, ShaderProgram *> shaderProgramMap;
	std::map<std::string, Texture *> textureMap;
	std::map<std::string, PoseLibrary *> poseLibraryMap;
};

} /* namespace ts */
#endif /* RESOURCEMANAGER_H_ */
