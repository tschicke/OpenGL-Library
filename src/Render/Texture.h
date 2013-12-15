/*
 * Texture.h
 *
 *  Created on: Dec 14, 2013
 *      Author: Tyler
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

class Texture {
public:
	Texture();
	Texture(const char * texturePath);
	virtual ~Texture();

	bool loadDDS(const char * texturePath);

	void bindTexture();
	static void unbindTexture();
protected:
	int textureID;

};

#endif /* TEXTURE_H_ */
