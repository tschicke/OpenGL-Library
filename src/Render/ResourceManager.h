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
#include "ShaderProgram.h"
#include "Texture.h"

namespace ts {

class ResourceManager {
public:
	static ResourceManager * getResourceManger();

	bool loadMeshFromFile(std::string meshName);
	bool loadMeshFromData(std::string meshName, float * vertexData, unsigned int * indexData, int numVertices, int numIndices, bool textured);
	bool loadShaderProgram(std::string vertexShaderName, std::string fragmentShaderName);
	bool loadTexture(std::string textureName);

	bool modifyMeshVertexData(std::string meshName, float * vertexData, int numElements, int offset);
	bool modifyMeshIndexData(std::string meshName, unsigned int * indexData, int numIndices, int offset);

	Mesh * getMesh(std::string meshName);
	ShaderProgram * getShaderProgram(std::string vertexShaderName, std::string fragmentShaderName);
	Texture * getTexture(std::string textureName);

	void deleteMesh(std::string meshName);
	void deleteShaderProgram(std::string shaderProgramName);
	void deleteTexture(std::string textureName);

	void cleanupMeshes();
	void cleanupShaderPrograms();
	void cleanupTextures();

	void cleanupAll();

private:
	ResourceManager();
	virtual ~ResourceManager();

	static ResourceManager resourceManager;

	std::map<std::string, Mesh *> meshMap;
	std::map<std::string, ShaderProgram *> shaderProgramMap;
	std::map<std::string, Texture *> textureMap;
};

} /* namespace ts */
#endif /* RESOURCEMANAGER_H_ */
