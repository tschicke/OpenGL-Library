//textureShader.frag
#version 330

in vec2 UV;
in vec3 normal;

out vec3 color;

uniform sampler2D myTextureSampler;

void main(){
	float diffuseIntensity = max(dot(normalize(normal), normalize(vec3(1, 1, 1))), 0);
	float ambientIntensity = 0.2f;

	vec2 glUV;
	glUV.x = UV.x;
	glUV.y = 1.0 - UV.y;
	color = texture2D(myTextureSampler, glUV).rgb * (diffuseIntensity + ambientIntensity);
}