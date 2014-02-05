/*
 * Shader.h
 *
 *  Created on: Feb 5, 2014
 *      Author: Tyler
 */

#ifndef SHADER_H_
#define SHADER_H_

namespace ts {

class Shader {
public:
	Shader();
	virtual ~Shader();

	friend class ResourceManager;
private:
	unsigned int shaderID;
	unsigned int shaderType;
};

} /* namespace ts */
#endif /* SHADER_H_ */
