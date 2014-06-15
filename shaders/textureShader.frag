#version 330

uniform sampler2D textureSampler;

in vec2 UV;
in vec3 normal;

out vec3 color;

void main(){
	vec3 normalizedNormal = normalize(normal);
	float diffuseIntensity = max(dot(normalizedNormal, normalize(vec3(1, 1, 1))), 0);
	float ambientIntensity = 0.2f;

	vec2 glUV;
	glUV.x = UV.x;
	glUV.y = 1.0 - UV.y;
	color = texture2D(textureSampler, glUV).rgb * (ambientIntensity + diffuseIntensity);
}