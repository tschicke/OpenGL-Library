/*
 * Texture.cpp
 *
 *  Created on: Dec 14, 2013
 *      Author: Tyler
 */

#include "Texture.h"

#include <gl/glew.h>
#include <gl/gl.h>

#include <iostream>
#include <fstream>

Texture::Texture() {
	textureID = -1;
}

Texture::Texture(const char* texturePath) {
	loadDDS(texturePath);
}

Texture::~Texture() {
}

void Texture::bindTexture(){
	if(textureID == -1) return;
	glBindTexture(GL_TEXTURE_2D, textureID);
}

bool Texture::loadDDS(const char* texturePath) {
	std::ifstream file(texturePath);
	if(!file.is_open()){
		std::cerr << "ERROR: Invalid Texture File Path: " << texturePath << "\n";
		return false;
	}

	char fileCode[4];
	file.read(fileCode, 4);
	if(*(unsigned int *) fileCode != 0x20534444){
		file.close();
		std::cerr << "ERROR: File " << texturePath << " not a .DDS File\n";
		return false;
	}

	return true;
}

void Texture::unbindTexture(){
	glBindTexture(GL_TEXTURE_2D, 0);
}

