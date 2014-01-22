/*
 * ResourceManager.cpp
 *
 *  Created on: Jan 22, 2014
 *      Author: Tyler
 */

#include "ResourceManager.h"

#include <iostream>
#include <fstream>

#include <gl/glew.h>
#include <gl/gl.h>

namespace ts {

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
}

bool ResourceManager::loadMesh(std::string meshName) {
	return false;
}

bool ResourceManager::loadShaderProgram(std::string shaderProgramName) {
	return false;
}

bool ResourceManager::loadTexture(std::string textureName) {
	if(textureMap.find(textureName) != textureMap.end()){
		std::cerr << "Error loading texture: " << textureName << " - " << textureName << " is already loaded" << std::endl;
	}

	Texture * texture = new Texture;

	std::ifstream file(textureName.c_str());
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



	return true;
}

Mesh * ResourceManager::getMesh(std::string meshName) {
	if (meshMap.find(meshName) == meshMap.end()) { //Does not contain
		bool load = loadMesh(meshName);
		if (!load) {
			return NULL;
		}
	}
	return meshMap.at(meshName);
}

ShaderProgram * ResourceManager::getShaderProgram(std::string shaderProgramName) {
	if (shaderProgramMap.find(shaderProgramName) == shaderProgramMap.end()) { //Does not contain
		bool load = loadShaderProgram(shaderProgramName);
		if (!load) {
			return NULL;
		}
	}
	return shaderProgramMap.at(shaderProgramName);
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

} /* namespace ts */
