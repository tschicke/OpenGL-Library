//colorShader.vert
#version 330

uniform mat4 MVPMatrix;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal;

out vec3 color;

void main(){
	color = vertexColor;
		
	vec4 position = vec4(vertexPosition, 1);
	gl_Position = MVPMatrix * position;
}