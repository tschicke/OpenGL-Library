#version 330

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec2 index;
layout(location = 4) in vec2 weights;

uniform mat4 Bones[20];
uniform mat4 MVPMatrix;

out vec2 UV;
out vec3 normal;

void main(){
	UV = vertexUV;
	
	mat4 modelMatrix = Bones[int(index.x)] * weights.x + Bones[int(index.y)] * weights.y;
	normal = (modelMatrix * vec4(vertexNormal, 0)).xyz;
	gl_Position = MVPMatrix * modelMatrix * vec4(vertexPosition, 1);
}