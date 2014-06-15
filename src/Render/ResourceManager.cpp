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

#include <string>
#include <string.h>
#include <sstream>
#include <vector>

#ifdef _WIN32
#include <gl/glew.h>
#elif defined __linux__
#include <GL/glew.h>
#endif

namespace ts {

ResourceManager ResourceManager::resourceManager;

ResourceManager* ResourceManager::getResourceManger() {
	return &resourceManager;
}

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
}

bool ResourceManager::loadMeshFromFile(std::string meshName) {
	if (meshMap.find(meshName) != meshMap.end()) {
		std::cerr << "Error loading mesh: " << meshName << " - mesh with name " << meshName << " is already loaded" << std::endl;
		return true;
	}

	std::ifstream meshFile;
	meshFile.open(("models/" + meshName + ".mesh").c_str());

	if (!meshFile.is_open()) {
		std::cerr << "Error loading mesh: " << meshName << " - could not open file " << meshName << ".mesh" << std::endl;
		meshFile.close();
		return false;
	}

	std::string header;
	getline(meshFile, header);
	if (header.compare("gmdl") != 0) {
		std::cerr << "Error loading mesh: " << meshName << " - file has incorrect header" << std::endl;
		meshFile.close();
		return false;
	}

	unsigned int numVertices, numIndices;
	std::string nums;
	getline(meshFile, nums);
	std::stringstream stream(nums);
	stream >> numVertices >> numIndices;
	std::vector<float> vertexData;
	vertexData.reserve(numVertices * 8); //Times number of floats per vertex
	std::vector<unsigned int> indexData;
	indexData.reserve(numIndices);

	std::string line;
	while (getline(meshFile, line)) {
		std::string prefix = line.substr(0, 1);
		if (prefix == "v") {
			std::stringstream stream(line.substr(1));
			float x, y, z;
			stream >> x >> y >> z;
			vertexData.push_back(x);
			vertexData.push_back(y);
			vertexData.push_back(z);
		} else if (prefix == "t") {
			std::stringstream stream(line.substr(1));
			float u, v;
			stream >> u >> v;
			vertexData.push_back(u);
			vertexData.push_back(v);
		} else if (prefix == "n") {
			std::stringstream stream(line.substr(1));
			float x, y, z;
			stream >> x >> y >> z;
			vertexData.push_back(x);
			vertexData.push_back(y);
			vertexData.push_back(z);
		} else if (prefix == "i") {
			std::stringstream stream(line.substr(1));
			unsigned int i1, i2, i3;
			stream >> i1 >> i2 >> i3;
			indexData.push_back(i1);
			indexData.push_back(i2);
			indexData.push_back(i3);
		}
	}

	meshFile.close();

	bool loaded = loadMeshFromData(meshName, vertexData.data(), indexData.data(), numVertices, numIndices, true);

	return loaded;
}

bool ResourceManager::loadMeshFromData(std::string meshName, float* vertexData, unsigned int* indexData, int numVertices, int numIndices, bool textured) {
	if (meshMap.find(meshName) != meshMap.end()) {
		std::cerr << "Error loading mesh: " << meshName << " - mesh with name " << meshName << " is already loaded" << std::endl;
		return true;
	}
	if (vertexData == NULL || indexData == NULL) {
		std::cerr << "Error loading mesh: " << meshName << " - vertexData or indexData is NULL" << std::endl;
		return false;
	}
	if (numVertices == 0 || numIndices == 0) {
		std::cerr << "Error loading mesh: " << meshName << " - numVertices or numIndices is 0" << std::endl;
		return false;
	}

	Mesh * mesh = new Mesh;
	mesh->numVertices = numVertices;
	mesh->numIndices = numIndices;
	mesh->textured = textured;
	unsigned int * vertexArrayID = &(mesh->vertexID);
	unsigned int * indexArrayID = &(mesh->indexID);

	int vertexSize = 3;
	int colorSize = (textured ? 2 : 3);
	int normalSize = 3;

	glGenBuffers(1, vertexArrayID);
	glGenBuffers(1, indexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, *vertexArrayID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * (vertexSize + colorSize + normalSize), vertexData, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexArrayID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, indexData, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	meshMap.insert(std::pair<std::string, Mesh *>(meshName, mesh));

	return true;
}

bool ResourceManager::loadAnimatedMeshFromFile(std::string animatedMeshName) {
	if (animatedMeshMap.find(animatedMeshName) != animatedMeshMap.end()) {
		std::cerr << "Error loading mesh: " << animatedMeshName << " - mesh with name " << animatedMeshName << " is already loaded" << std::endl;
		return true;
	}

	std::ifstream animatedMeshFile;
	animatedMeshFile.open(("models/" + animatedMeshName + ".amesh").c_str());

	if (!animatedMeshFile.is_open()) {
		std::cerr << "Error loading mesh: " << animatedMeshName << " - could not open file " << animatedMeshName << ".amesh" << std::endl;
		animatedMeshFile.close();
		return false;
	}

	std::string header;
	getline(animatedMeshFile, header);
	if (header.compare("amdl") != 0) {
		std::cerr << "Error loading mesh: " << animatedMeshName << " - file has incorrect header" << std::endl;
		animatedMeshFile.close();
		return false;
	}

	unsigned int numVertices, numIndices, numBones;
	std::string nums;
	getline(animatedMeshFile, nums);
	std::stringstream stream(nums);
	stream >> numVertices >> numIndices >> numBones;
	std::vector<float> vertexData;
	vertexData.reserve(numVertices * 12); //Times number of floats per vertex; Position(3), UV(2), Normal(3), Bone Index(2), Bone Weight(2)
	std::vector<float> boneData;
	boneData.reserve(numBones * 5);
	std::vector<unsigned int> indexData;
	indexData.reserve(numIndices);

	std::string line;
	while (getline(animatedMeshFile, line)) {
		std::string prefix = line.substr(0, 1);
		if (prefix == "v") { //Vertex
			std::stringstream stream(line.substr(1));
			float x, y, z;
			stream >> x >> y >> z;
			vertexData.push_back(x);
			vertexData.push_back(y);
			vertexData.push_back(z);
		} else if (prefix == "t") { //Texture Coordinate
			std::stringstream stream(line.substr(1));
			float u, v;
			stream >> u >> v;
			vertexData.push_back(u);
			vertexData.push_back(v);
		} else if (prefix == "n") { //Normal
			std::stringstream stream(line.substr(1));
			float x, y, z;
			stream >> x >> y >> z;
			vertexData.push_back(x);
			vertexData.push_back(y);
			vertexData.push_back(z);
		} else if (prefix == "b") { //Bone
			std::stringstream stream(line.substr(1));
			float b1, b2;
			stream >> b1 >> b2;
			vertexData.push_back(b1);
			vertexData.push_back(b2);
		} else if (prefix == "w") { //Weight
			std::stringstream stream(line.substr(1));
			float w1, w2;
			stream >> w1 >> w2;
			vertexData.push_back(w1);
			vertexData.push_back(w2);
		} else if (prefix == "s") { //Skeleton
			std::stringstream stream(line.substr(1));
			float pX, pY, pZ, bI, pI; //Position x, Position y, Position Z, Bone index, Parent Index
			stream >> pX >> pY >> pZ >> bI >> pI;
			boneData.push_back(pX);
			boneData.push_back(pY);
			boneData.push_back(pZ);
			boneData.push_back(bI);
			boneData.push_back(pI);
		} else if (prefix == "i") { //Index
			std::stringstream stream(line.substr(1));
			unsigned int i1, i2, i3;
			stream >> i1 >> i2 >> i3;
			indexData.push_back(i1);
			indexData.push_back(i2);
			indexData.push_back(i3);
		}
	}

	animatedMeshFile.close();

	bool loaded = loadAnimatedMeshFromData(animatedMeshName, vertexData.data(), boneData.data(), indexData.data(), numVertices, numIndices, numBones, true);

	return loaded;
}

bool ResourceManager::loadAnimatedMeshFromData(std::string animatedMeshName, float* vertexData, float * boneData, unsigned int* indexData, int numVertices, int numIndices, int numBones, bool textured) {
	if (animatedMeshMap.find(animatedMeshName) != animatedMeshMap.end()) {
		std::cerr << "Error loading mesh: " << animatedMeshName << " - mesh with name " << animatedMeshName << " is already loaded" << std::endl;
		return true;
	}
	if (vertexData == NULL || indexData == NULL) {
		std::cerr << "Error loading mesh: " << animatedMeshName << " - vertexData or indexData is NULL" << std::endl;
		return false;
	}
	if (numVertices == 0 || numIndices == 0) {
		std::cerr << "Error loading mesh: " << animatedMeshName << " - numVertices or numIndices is 0" << std::endl;
		return false;
	}

	AnimatedMesh * mesh = new AnimatedMesh;
	mesh->numVertices = numVertices;
	mesh->numIndices = numIndices;
	mesh->textured = textured;
	Skeleton * skeleton = new Skeleton;
	skeleton->numBones = numBones;
	skeleton->boneArray = new Node[numBones];
	skeleton->modelMatrixArray = new ts::Vector::mat4[numBones];

	for (int i = 0; i < numBones; ++i) {
		Node node;
		ts::Vector::vec3 nodePosition;
		nodePosition.x = boneData[(i * 5)];
		nodePosition.y = boneData[(i * 5) + 1];
		nodePosition.z = boneData[(i * 5) + 2];
		node.position = nodePosition;
		node.nodeIndex = boneData[(i * 5) + 3];
		node.parentNodeIndex = boneData[(i * 5) + 4];

		skeleton->boneArray[i] = node;
	}

	mesh->defaultSkeleton = skeleton;

	unsigned int * vertexArrayID = &(mesh->vertexID);
	unsigned int * indexArrayID = &(mesh->indexID);

	int vertexSize = 3;
	int colorSize = (textured ? 2 : 3);
	int normalSize = 3;
	int boneSize = 2;
	int weightSize = 2;

	glGenBuffers(1, vertexArrayID);
	glGenBuffers(1, indexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, *vertexArrayID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * (vertexSize + colorSize + normalSize + boneSize + weightSize), vertexData, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexArrayID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, indexData, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::pair<std::string, AnimatedMesh *> pair = std::pair<std::string, AnimatedMesh *>(animatedMeshName, mesh);

	animatedMeshMap.insert(pair);

	return true;
}

bool ResourceManager::loadShaderProgram(std::string vertexShaderName, std::string fragmentShaderName) {
	if (shaderProgramMap.find(vertexShaderName + fragmentShaderName) != shaderProgramMap.end()) {
		std::cerr << "Error loading shader program: " << vertexShaderName + fragmentShaderName << " - Shader program with shaders " << vertexShaderName << " and " << fragmentShaderName
				<< " is already loaded" << std::endl;
		return true;
	}

	ShaderProgram * shaderProgram = new ShaderProgram;
	shaderProgram->shaderProgramID = glCreateProgram();

	//Load Vertex Shader
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(("shaders/" + vertexShaderName + ".vert").c_str(), std::ios::in);
	if (vertexShaderStream.is_open()) {
		std::string line = "";
		while (getline(vertexShaderStream, line)) {
			vertexShaderCode += '\n' + line;
		}
		vertexShaderStream.close();
	} else {
		std::cerr << "Error loading shader program: " << vertexShaderName + fragmentShaderName << " - " << vertexShaderName << ".vert could not be opened" << std::endl;
		glDeleteProgram(shaderProgram->shaderProgramID);
		return false;
	}
	//Compile Vertex Shader
	unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	const char * vertexShaderCodePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexShaderCodePointer, NULL);
	glCompileShader(vertexShaderID);
	//Check Vertex Shader
	int vertexShaderCompilationStatus = 0;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &vertexShaderCompilationStatus);
	if (vertexShaderCompilationStatus == GL_FALSE) {
		char infoLog[1024];
		int logLength;
		glGetShaderInfoLog(vertexShaderID, 1024, &logLength, infoLog);
		std::cerr << "Error compiling vertex shader:" << vertexShaderName << " - Compiler returned " << std::endl << infoLog << std::endl;
		glDeleteShader(vertexShaderID);
		glDeleteProgram(shaderProgram->shaderProgramID);
		return false;
	}
	//Attach Vertex Shader
	glAttachShader(shaderProgram->shaderProgramID, vertexShaderID);

	//Load Fragment Shader
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(("shaders/" + fragmentShaderName + ".frag").c_str(), std::ios::in);
	if (fragmentShaderStream.is_open()) {
		std::string line = "";
		while (getline(fragmentShaderStream, line)) {
			fragmentShaderCode += '\n' + line;
		}
		fragmentShaderStream.close();
	} else {
		std::cerr << "Error loading shader program: " << vertexShaderName + fragmentShaderName << " - " << fragmentShaderName << ".frag could not be opened" << std::endl;
		glDeleteShader(vertexShaderID);
		glDeleteProgram(shaderProgram->shaderProgramID);
		return false;
	}
	//Compile Fragment Shader
	unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	const char * fragmentShaderCodePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentShaderCodePointer, NULL);
	glCompileShader(fragmentShaderID);
	//Check Fragment Shader
	int fragmentShaderCompilationStatus = 0;
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &fragmentShaderCompilationStatus);
	if (fragmentShaderCompilationStatus == GL_FALSE) {
		char infoLog[1024];
		int logLength;
		glGetShaderInfoLog(fragmentShaderID, 1024, &logLength, infoLog);
		std::cerr << "Error compiling fragment shader:" << fragmentShaderName << " - Compiler returned " << std::endl << infoLog << std::endl;
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteProgram(shaderProgram->shaderProgramID);
		return false;
	}
	//Attach Fragment Shader
	glAttachShader(shaderProgram->shaderProgramID, fragmentShaderID);

	//Link Shader Program
	glLinkProgram(shaderProgram->shaderProgramID);
	//Check Shader Program
	int linkStatus = 0;
	glGetProgramiv(shaderProgram->shaderProgramID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE) {
		std::cerr << "Error linking shader program: " << vertexShaderName + fragmentShaderName << std::endl;
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteProgram(shaderProgram->shaderProgramID);
		return false;
	}

	//Delete Vertex Shader
	glDeleteShader(vertexShaderID);
	//Delete Fragment Shader
	glDeleteShader(fragmentShaderID);

	shaderProgramMap.insert(std::pair<std::string, ShaderProgram *>((vertexShaderName + fragmentShaderName), shaderProgram));

	return true;
}

bool ResourceManager::loadTexture(std::string textureName) {
	if (textureMap.find(textureName) != textureMap.end()) {
		std::cerr << "Error loading texture: " << textureName << " - " << textureName << " is already loaded" << std::endl;
		return true;
	}

	Texture * texture = new Texture;

	std::ifstream file(("res/" + textureName + ".DDS").c_str());
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
	for (unsigned int level = 0; level < mipmapCount && (width || height); level++) {
		unsigned int size = MathHelper::max((width / 4), 1) * MathHelper::max((height / 4), 1) * block_size;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	delete buffer;

	glBindTexture(GL_TEXTURE_2D, 0);

	textureMap.insert(std::pair<std::string, Texture *>(textureName, texture));

	return true;
}

bool ResourceManager::modifyMeshVertexData(std::string meshName, float * vertexData, int numVertices, int vertexOffset) {
	std::map<std::string, Mesh *>::iterator location = meshMap.find(meshName);
	if (location == meshMap.end()) {
		std::cout << "Error modifying mesh " << meshName << ": mesh is not loaded and cannot be modified" << std::endl;
		return false;
	}
	Mesh * mesh = location->second;

	if (vertexOffset + numVertices > mesh->numVertices) {
		std::cout << "Error modifying mesh " << meshName << ": numVertices or vertexOffset is too large" << std::endl;
		return false;
	}
	if (vertexData == NULL) {
		std::cout << "Error modifying mesh " << meshName << ": vertexData is null" << std::endl;
		return false;
	}
	if (numVertices == 0) {
		return false;
	}

	unsigned int vertexID = mesh->vertexID;

	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glBufferSubData(GL_ARRAY_BUFFER, vertexOffset * 3 * sizeof(float), numVertices * 3 * sizeof(float), vertexData);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

bool ResourceManager::modifyMeshTextureData(std::string meshName, float * textureData, int numUVs, int textureOffset) {
	std::map<std::string, Mesh *>::iterator location = meshMap.find(meshName);
	if (location == meshMap.end()) {
		std::cout << "Error modifying mesh " << meshName << ": mesh is not loaded and cannot be modified" << std::endl;
		return false;
	}
	Mesh * mesh = location->second;

	if (textureOffset + numUVs > mesh->numVertices) {
		std::cout << "Error modifying mesh " << meshName << ": numVertices or vertexOffset is too large" << std::endl;
		return false;
	}
	if (textureData == NULL) {
		std::cout << "Error modifying mesh " << meshName << ": vertexData is null" << std::endl;
		return false;
	}
	if (numUVs == 0) {
		return false;
	}

	unsigned int vertexID = mesh->vertexID;

	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glBufferSubData(GL_ARRAY_BUFFER, ((textureOffset * 2) + (mesh->numVertices * 3)) * sizeof(float), numUVs * 2 * sizeof(float), textureData);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

bool ResourceManager::modifyMeshNormalData(std::string meshName, float * normalData, int numNormals, int normalOffset) {
	std::map<std::string, Mesh *>::iterator location = meshMap.find(meshName);
	if (location == meshMap.end()) {
		std::cout << "Error modifying mesh " << meshName << ": mesh is not loaded and cannot be modified" << std::endl;
		return false;
	}
	Mesh * mesh = location->second;

	if (normalOffset + numNormals > mesh->numVertices) {
		std::cout << "Error modifying mesh " << meshName << ": numVertices or vertexOffset is too large" << std::endl;
		return false;
	}
	if (normalData == NULL) {
		std::cout << "Error modifying mesh " << meshName << ": vertexData is null" << std::endl;
		return false;
	}
	if (numNormals == 0) {
		return false;
	}

	unsigned int vertexID = mesh->vertexID;

	glBindBuffer(GL_ARRAY_BUFFER, vertexID);
	glBufferSubData(GL_ARRAY_BUFFER, ((normalOffset * 3) + (mesh->numVertices * (3 + (mesh->textured ? 2 : 3)))) * sizeof(float), numNormals * 3 * sizeof(float), normalData);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

bool ResourceManager::modifyMeshIndexData(std::string meshName, unsigned int * indexData, int numIndices, int offset) {
	std::map<std::string, Mesh *>::iterator location = meshMap.find(meshName);
	if (location == meshMap.end()) {
		std::cout << "Error modifying mesh " << meshName << ": mesh is not loaded and cannot be modified" << std::endl;
		return false;
	}
	Mesh * mesh = location->second;

	if (offset + numIndices > mesh->numIndices) {
		std::cout << "Error modifying mesh " << meshName << ": numElements or offset is too large" << std::endl;
		return false;
	}
	if (indexData == NULL) {
		std::cout << "Error modifying mesh " << meshName << ": vertexData is null" << std::endl;
	}
	if (numIndices == 0) {
		return false;
	}

	unsigned int indexID = mesh->indexID;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(unsigned int), numIndices * sizeof(unsigned int), indexData);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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

AnimatedMesh * ResourceManager::getAnimatedMesh(std::string animatedMeshName) {
	if (animatedMeshMap.find(animatedMeshName) == animatedMeshMap.end()) { //Does not contain
		bool load = loadAnimatedMeshFromFile(animatedMeshName);
		if (!load) {
			return NULL;
		}
	}
	return animatedMeshMap.at(animatedMeshName);
}

ShaderProgram * ResourceManager::getShaderProgram(std::string vertexShaderName, std::string fragmentShaderName) {
	if (shaderProgramMap.find(vertexShaderName + fragmentShaderName) == shaderProgramMap.end()) { //Does not contain
		bool load = loadShaderProgram(vertexShaderName, fragmentShaderName);
		if (!load) {
			return NULL;
		}
	}
	return shaderProgramMap.at(vertexShaderName + fragmentShaderName);
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
	std::map<std::string, Mesh *>::iterator location = meshMap.find(meshName);
	if (location == meshMap.end()) {
		std::cout << "Error deleting mesh " << meshName << ": mesh not loaded" << std::endl;
		return;
	}
	Mesh * mesh = location->second;
	glDeleteBuffers(1, &(mesh->vertexID));
	glDeleteBuffers(1, &(mesh->indexID));
	meshMap.erase(meshName);
	delete mesh;
}

void ResourceManager::deleteShaderProgram(std::string shaderProgramName) {
	std::map<std::string, ShaderProgram *>::iterator location = shaderProgramMap.find(shaderProgramName);
	if (location == shaderProgramMap.end()) {
		std::cout << "Error deleting shader program " << shaderProgramName << ": shader program not loaded" << std::endl;
		return;
	}
	ShaderProgram * shaderProgram = location->second;
	glDeleteProgram(shaderProgram->shaderProgramID);
	shaderProgramMap.erase(shaderProgramName);
	delete shaderProgram;
}

void ResourceManager::deleteTexture(std::string textureName) {
	std::map<std::string, Texture *>::iterator location = textureMap.find(textureName);
	if (location == textureMap.end()) {
		std::cout << "Error deleting texture " << textureName << ": texture not loaded" << std::endl;
		return;
	}
	Texture * texture = location->second;
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
