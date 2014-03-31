/*
 * Texture.cpp
 *
 *  Created on: Dec 14, 2013
 *      Author: Tyler
 */

#include "Texture.h"

#ifdef _WIN32
#include <gl/glew.h>
#elif defined __linux__
#include <GL/glew.h>
#endif

#include <iostream>
#include <fstream>

namespace ts{

Texture::Texture() {
	textureID = -1;
}

Texture::~Texture() {
}

void Texture::bindTexture(){
	if(textureID == (unsigned int) -1) {
		return;
	}
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbindTexture(){
	glBindTexture(GL_TEXTURE_2D, 0);
}

}//namespace ts

