#version 330

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 NormalMatrix, MVPMatrix;

smooth out vec3 position;
smooth out vec2 UV;
smooth out vec3 normal;

void main(){
	vec4 tempPosition = MVPMatrix * vec4(vertexPosition, 1);
	gl_Position = tempPosition;
	
	position = tempPosition.xyz;
	UV.x = vertexUV.x;
	UV.y = 1 - vertexUV.y;
	normal = (NormalMatrix * vec4(vertexNormal, 0)).xyz;
}