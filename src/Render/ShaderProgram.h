/*
 * ShaderProgram.h
 *
 *  Created on: Feb 5, 2014
 *      Author: Tyler
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

namespace ts {

class ShaderProgram {
public:
	ShaderProgram();
	virtual ~ShaderProgram();

	void useShaderProgram();
	static void disableShaderProgram();
};

} /* namespace ts */
#endif /* SHADERPROGRAM_H_ */
