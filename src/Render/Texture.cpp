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

namespace ts{

Texture::Texture() {
	textureID = -1;
}

Texture::~Texture() {
}

void Texture::bindTexture(){
	if(textureID == (unsigned int) -1) return;
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbindTexture(){
	glBindTexture(GL_TEXTURE_2D, 0);
}

}//namespace ts

