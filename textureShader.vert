//textureShader.vert
#version 330

uniform mat4 MVPMatrix;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec2 UV;

void main(){
	UV = vertexUV;//TODO flip texture to OGL coords
		
	vec4 position = vec4(vertexPosition, 1);
	gl_Position = MVPMatrix * position;
}