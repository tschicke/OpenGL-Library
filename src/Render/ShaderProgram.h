/*
 * ShaderProgram.h
 *
 *  Created on: Feb 5, 2014
 *      Author: Tyler
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include "../Vector/Vector.h"
#include "../Vector/Matrix.h"

namespace ts {

class ShaderProgram {
public:
	ShaderProgram();
	virtual ~ShaderProgram();

	void useShaderProgram();
	static void disableShaderProgram();

	// Setting vectors
	void setUniform(const char * sName, ts::Vector::vec2* vVectors, int iCount = 1);
	void setUniform(const char * sName, const ts::Vector::vec2 vVector);
	void setUniform(const char * sName, ts::Vector::vec3* vVectors, int iCount = 1);
	void setUniform(const char * sName, const ts::Vector::vec3 vVector);
	void setUniform(const char * sName, ts::Vector::vec4* vVectors, int iCount = 1);
	void setUniform(const char * sName, const ts::Vector::vec4 vVector);

	// Setting floats
	void setUniform(const char * sName, float* fValues, int iCount = 1);
	void setUniform(const char * sName, const float fValue);

	// Setting integers
	void setUniform(const char * sName, int* iValues, int iCount = 1);
	void setUniform(const char * sName, const int iValue);

	// Setting 4x4 matrices
	void setUniform(const char * sName, ts::Vector::mat4* mMatrices, int iCount = 1);
	void setUniform(const char * sName, const ts::Vector::mat4 mMatrix);

	friend class ResourceManager;
private:
	unsigned int shaderProgramID;
};

} /* namespace ts */
#endif /* SHADERPROGRAM_H_ */
