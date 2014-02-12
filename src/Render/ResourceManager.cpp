/*
 * ResourceManager.cpp
 *
 *  Created on: Jan 22, 2014
 *      Author: Tyler
 */

#include "ResourceManager.h"

#include "../Util/MathHelper.h"

#include <iostream>
#include <fstream>

#include <gl/glew.h>
#include <gl/gl.h>

namespace ts {

ResourceManager ResourceManager::resourceManager;

ResourceManager* ResourceManager::getResourceManger() {
	return &resourceManager;
}

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
}

bool ResourceManager::loadMeshFromFile(std::string meshName) {
	return false;
}

bool ResourceManager::loadMeshFromData(std::string meshName, float* vertexData, unsigned int* indexData, int numVertices, int numIndices, bool textured) {
	if (meshMap.find(meshName) != meshMap.end()) {
		std::cerr << "Error loading mesh: " << meshName << " - " << meshName << " is already loaded" << std::endl;
		return false;
	}
	if (vertexData == NULL || indexData == NULL) {
		std::cerr << "Error loading mesh: " << meshName << " - vertexData or indexData is NULL" << std::endl;
		return false;
	}
	if (numVertices == 0 || numIndices == 0) {
		std::cerr << "Error loading mesh: " << meshName << " - numVertices or numIndices is 0" << std::endl;
		return false;
	}

	Mesh * mesh = new Mesh;
	mesh->numVertices = numVertices;
	mesh->numIndices = numIndices;
	mesh->textured = textured;
	unsigned int * vertexArrayID = &(mesh->vertexID);
	unsigned int * indexArrayID = &(mesh->indexID);

	int vertexSize = 3;
	int colorSize = (textured ? 2 : 3);
	int normalSize = 3;

	glGenBuffers(1, vertexArrayID);
	glGenBuffers(1, indexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, *vertexArrayID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * (vertexSize + colorSize + normalSize), vertexData, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexArrayID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, indexData, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	meshMap.insert(std::pair<std::string, Mesh *>(meshName, mesh));

	return true;
}

bool ResourceManager::loadShaderProgram(std::string vertexShaderName, std::string fragmentShaderName) {
	if (shaderProgramMap.find(vertexShaderName + fragmentShaderName) != shaderProgramMap.end()) {
		std::cerr << "Error loading shader program: " << vertexShaderName + fragmentShaderName << " - Shader program with shaders " << vertexShaderName << " and " << fragmentShaderName
				<< " is already loaded" << std::endl;
		return true;
	}

	ShaderProgram * shaderProgram = new ShaderProgram;
	shaderProgram->shaderProgramID = glCreateProgram();

	//Load Vertex Shader
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream((vertexShaderName + ".vert").c_str(), std::ios::in);
	if (vertexShaderStream.is_open()) {
		std::string line = "";
		while (getline(vertexShaderStream, line)) {
			vertexShaderCode += '\n' + line;
		}
		vertexShaderStream.close();
	} else {
		std::cerr << "Error loading shader program: " << vertexShaderName + fragmentShaderName << " - " << vertexShaderName << ".vert could not be opened" << std::endl;
		glDeleteProgram(shaderProgram->shaderProgramID);
		return false;
	}
	//Compile Vertex Shader
	unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	const char * vertexShaderCodePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexShaderCodePointer, NULL);
	glCompileShader(vertexShaderID);
	//Check Vertex Shader
	int vertexShaderCompilationStatus = 0;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &vertexShaderCompilationStatus);
	if (vertexShaderCompilationStatus == GL_FALSE) {
		char infoLog[1024];
		int logLength;
		glGetShaderInfoLog(vertexShaderID, 1024, &logLength, infoLog);
		std::cerr << "Error compiling vertex shader:" << vertexShaderName << " - Compiler returned " << std::endl << infoLog << std::endl;
		glDeleteShader(vertexShaderID);
		glDeleteProgram(shaderProgram->shaderProgramID);
		return false;
	}
	//Attach Vertex Shader
	glAttachShader(shaderProgram->shaderProgramID, vertexShaderID);

	//Load Fragment Shader
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream((fragmentShaderName + ".frag").c_str(), std::ios::in);
	if (fragmentShaderStream.is_open()) {
		std::string line = "";
		while (getline(fragmentShaderStream, line)) {
			fragmentShaderCode += '\n' + line;
		}
		fragmentShaderStream.close();
	} else {
		std::cerr << "Error loading shader program: " << vertexShaderName + fragmentShaderName << " - " << fragmentShaderName << ".frag could not be opened" << std::endl;
		glDeleteShader(vertexShaderID);
		glDeleteProgram(shaderProgram->shaderProgramID);
		return false;
	}
	//Compile Fragment Shader
	unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	const char * fragmentShaderCodePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentShaderCodePointer, NULL);
	glCompileShader(fragmentShaderID);
	//Check Fragment Shader
	int fragmentShaderCompilationStatus = 0;
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &fragmentShaderCompilationStatus);
	if (fragmentShaderCompilationStatus == GL_FALSE) {
		char infoLog[1024];
		int logLength;
		glGetShaderInfoLog(fragmentShaderID, 1024, &logLength, infoLog);
		std::cerr << "Error compiling fragment shader:" << fragmentShaderName << " - Compiler returned " << std::endl << infoLog << std::endl;
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteProgram(shaderProgram->shaderProgramID);
		return false;
	}
	//Attach Fragment Shader
	glAttachShader(shaderProgram->shaderProgramID, fragmentShaderID);

	//Link Shader Program
	glLinkProgram(shaderProgram->shaderProgramID);
	//Check Shader Program
	int linkStatus = 0;
	glGetProgramiv(shaderProgram->shaderProgramID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE) {
		std::cerr << "Error linking shader program: " << vertexShaderName + fragmentShaderName << std::endl;
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteProgram(shaderProgram->shaderProgramID);
		return false;
	}

	//Delete Vertex Shader
	glDeleteShader(vertexShaderID);
	//Delete Fragment Shader
	glDeleteShader(fragmentShaderID);

	shaderProgramMap.insert(std::pair<std::string, ShaderProgram *>((vertexShaderName + fragmentShaderName), shaderProgram));

	return true;
}

bool ResourceManager::loadTexture(std::string textureName) {
	if (textureMap.find(textureName) != textureMap.end()) {
		std::cerr << "Error loading texture: " << textureName << " - " << textureName << " is already loaded" << std::endl;
		return false;
	}

	Texture * texture = new Texture;

	std::ifstream file((textureName + ".DDS").c_str());
	if (!file.is_open()) {
		std::cerr << "Error loading texture: " << textureName << " - invalid file name" << std::endl;
		return false;
	}

	char fileCode[4];
	file.read(fileCode, 4);
	if (*(unsigned int *) fileCode != 0x20534444) {
		file.close();
		std::cerr << "Error loading texture: " << textureName << " - file is not a .DDS file" << std::endl;
		return false;
	}

	char header[124];
	file.read(header, 124);

	unsigned int height = *(unsigned int *) &header[2 * 4];
	unsigned int width = *(unsigned int *) &header[3 * 4];
	unsigned int size = *(unsigned int *) &header[4 * 4];
	unsigned int mipmapCount = *(unsigned int *) &header[6 * 4];
	unsigned int pixelFormat = *(unsigned int *) &header[20 * 4];

	unsigned int bufferSize = (mipmapCount > 1 ? size * 1.5 : size);
	unsigned char *buffer = new unsigned char[bufferSize];
	file.read((char *) buffer, bufferSize);
	file.close();

	unsigned int format;
	switch (pixelFormat) {
	case 0x31545844: // Equivalent to "DXT1" in ASCII
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case 0x33545844: // Equivalent to "DXT3" in ASCII
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case 0x35545844: // Equivalent to "DXT5" in ASCII
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		std::cerr << "Error loading texture: " << textureName << " - Unrecognized DDS format - not DXT1, DXT3, or DXT5" << std::endl;
		delete buffer;
		return false;
	}

	unsigned int * textureID = &(texture->textureID);
	glGenTextures(1, textureID);
	glBindTexture(GL_TEXTURE_2D, *textureID);

	unsigned int block_size = ((format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16);
	unsigned int offset = 0;

	/*Load texture and mipmaps*/
	for (unsigned int level = 0; level < mipmapCount && (width || height); level++) {
		unsigned int size = MathHelper::max((width / 4), 1) * MathHelper::max((height / 4), 1) * block_size;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	delete buffer;

	glBindTexture(GL_TEXTURE_2D, 0);

	textureMap.insert(std::pair<std::string, Texture *>(textureName, texture));

	return true;
}

Mesh * ResourceManager::getMesh(std::string meshName) {
	if (meshMap.find(meshName) == meshMap.end()) { //Does not contain
		bool load = loadMeshFromFile(meshName);
		if (!load) {
			return NULL;
		}
	}
	return meshMap.at(meshName);
}

ShaderProgram * ResourceManager::getShaderProgram(std::string vertexShaderName, std::string fragmentShaderName) {
	if (shaderProgramMap.find(vertexShaderName + fragmentShaderName) == shaderProgramMap.end()) { //Does not contain
		bool load = loadShaderProgram(vertexShaderName, fragmentShaderName);
		if (!load) {
			return NULL;
		}
	}
	return shaderProgramMap.at(vertexShaderName + fragmentShaderName);
}

Texture * ResourceManager::getTexture(std::string textureName) {
	if (textureMap.find(textureName) == textureMap.end()) { //Does not contain
		bool load = loadTexture(textureName);
		if (!load) {
			return NULL;
		}
	}
	return textureMap.at(textureName);
}

void ResourceManager::deleteMesh(std::string meshName) {
}

void ResourceManager::deleteShaderProgram(std::string shaderProgramName) {
}

void ResourceManager::deleteTexture(std::string textureName) {
	if (textureMap.find(textureName) == textureMap.end()) {
		return;
	}
	Texture * texture = textureMap.at(textureName);
	glDeleteTextures(1, &(texture->textureID));
	textureMap.erase(textureName);
	delete texture;
}

void ResourceManager::cleanupMeshes() {
	std::map<std::string, Mesh *>::iterator iterator = meshMap.begin();
	while (iterator != meshMap.end()) {
		iterator = meshMap.erase(iterator);
	}
}

void ResourceManager::cleanupShaderPrograms() {
	std::map<std::string, ShaderProgram *>::iterator iterator = shaderProgramMap.begin();
	while (iterator != shaderProgramMap.end()) {
		iterator = shaderProgramMap.erase(iterator);
	}
}

void ResourceManager::cleanupTextures() {
	std::map<std::string, Texture *>::iterator iterator = textureMap.begin();
	while (iterator != textureMap.end()) {
		iterator = textureMap.erase(iterator);
	}
}

void ResourceManager::cleanupAll() {
	cleanupMeshes();
	cleanupShaderPrograms();
	cleanupTextures();
}

} /* namespace ts */
