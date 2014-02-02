/*
 * Texture.h
 *
 *  Created on: Dec 14, 2013
 *      Author: Tyler
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

namespace ts{

class Texture {
public:
	Texture();
	virtual ~Texture();

	void bindTexture();
	static void unbindTexture();

	friend class ResourceManager;
protected:
	unsigned int textureID;

};

}

#endif /* TEXTURE_H_ */
