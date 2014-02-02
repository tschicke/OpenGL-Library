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

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
}

bool ResourceManager::loadMeshFromFile(std::string meshName) {
	return false;
}

bool ResourceManager::loadShaderProgram(std::string shaderProgramName) {
	return false;
}

bool ResourceManager::loadTexture(std::string textureName) {
	if (textureMap.find(textureName) != textureMap.end()) {
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

	unsigned int * textureID = &(texture->textureID);
	glGenTextures(1, textureID);
	glBindTexture(GL_TEXTURE_2D, *textureID);

	unsigned int block_size = ((format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16);
	unsigned int offset = 0;

	/*Load texture and mipmaps*/
	for (unsigned int level = 0; level < 1 && (width || height); level++) {
		unsigned int size = MathHelper::max((width / 4), 1) * MathHelper::max((height / 4), 1) * block_size;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;
	}
	delete buffer;

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
