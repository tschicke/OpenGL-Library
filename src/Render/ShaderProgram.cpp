/*
 * ShaderProgram.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: Tyler
 */

#include "ShaderProgram.h"
#ifdef _WIN32
#include <gl/glew.h>
#elif defined __linux__
#include <GL/glew.h>
#endif

namespace ts {

ShaderProgram::ShaderProgram() {
	shaderProgramID = -1;
}

ShaderProgram::~ShaderProgram() {
}

void ShaderProgram::useShaderProgram() {
	glUseProgram(shaderProgramID);
}

void ShaderProgram::disableShaderProgram() {
	glUseProgram(0);
}

// Setting floats
void ShaderProgram::setUniform(const char * uniformName, float* floatPointer, int numFloats) {
	int uniformLocation = glGetUniformLocation(shaderProgramID, uniformName);
	glUniform1fv(uniformLocation, numFloats, floatPointer);
}

void ShaderProgram::setUniform(const char * uniformName, const float floatValue) {
	int uniformLocation = glGetUniformLocation(shaderProgramID, uniformName);
	glUniform1f(uniformLocation, floatValue);
}

// Setting vectors
void ShaderProgram::setUniform(const char * uniformName, ts::Vector::vec2* vectorPointer, int numVectors) {
	int uniformLocation = glGetUniformLocation(shaderProgramID, uniformName);
	glUniform2fv(uniformLocation, numVectors, (GLfloat*) vectorPointer);
}

void ShaderProgram::setUniform(const char * uniformName, const ts::Vector::vec2 vector) {
	int uniformLocation = glGetUniformLocation(shaderProgramID, uniformName);
	glUniform2fv(uniformLocation, 1, (GLfloat*) &vector);
}

void ShaderProgram::setUniform(const char * uniformName, ts::Vector::vec3* vectorPointer, int numVectors) {
	int uniformLocation = glGetUniformLocation(shaderProgramID, uniformName);
	glUniform3fv(uniformLocation, numVectors, (GLfloat*) vectorPointer);
}

void ShaderProgram::setUniform(const char * uniformName, const ts::Vector::vec3 vector) {
	int uniformLocation = glGetUniformLocation(shaderProgramID, uniformName);
	glUniform3fv(uniformLocation, 1, (GLfloat*) &vector);
}

void ShaderProgram::setUniform(const char * uniformName, ts::Vector::vec4* vectorPointer, int numVectors) {
	int uniformLocation = glGetUniformLocation(shaderProgramID, uniformName);
	glUniform4fv(uniformLocation, numVectors, (GLfloat*) vectorPointer);
}

void ShaderProgram::setUniform(const char * uniformName, const ts::Vector::vec4 vector) {
	int uniformLocation = glGetUniformLocation(shaderProgramID, uniformName);
	glUniform4fv(uniformLocation, 1, (GLfloat*) &vector);
}

// Setting 4x4 matrices
void ShaderProgram::setUniform(const char * uniformName, ts::Vector::mat4* matrixPointer, int numMatrices) {
	int uniformLocation = glGetUniformLocation(shaderProgramID, uniformName);
	glUniformMatrix4fv(uniformLocation, numMatrices, GL_FALSE, (GLfloat*) matrixPointer);
}

void ShaderProgram::setUniform(const char * uniformName, const ts::Vector::mat4 matrix) {
	int uniformLocation = glGetUniformLocation(shaderProgramID, uniformName);
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, (GLfloat*) &matrix);
}

// Setting integers
void ShaderProgram::setUniform(const char * uniformName, int* iValues, int iCount) {
	int uniformLocation = glGetUniformLocation(shaderProgramID, uniformName);
	glUniform1iv(uniformLocation, iCount, iValues);
}

void ShaderProgram::setUniform(const char * uniformName, const int intValue) {
	int uniformLocation = glGetUniformLocation(shaderProgramID, uniformName);
	glUniform1i(uniformLocation, intValue);
}

} /* namespace ts */
