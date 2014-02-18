//textureShader.vert
#version 330

uniform mat4 MVPMatrix;
uniform mat4 NormalMatrix;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec2 UV;
out vec3 normal;

void main(){
	UV = vertexUV;//TODO flip texture to OGL coords
	normal = (NormalMatrix * vec4(vertexNormal, 0)).xyz;
		
	vec4 position = vec4(vertexPosition, 1);
	gl_Position = MVPMatrix * position;
}