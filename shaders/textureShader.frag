//textureShader.frag
#version 330

//uniform float lightY;//For point light

//in vec3 position;
in vec2 UV;
in vec3 normal;

out vec3 color;

uniform sampler2D myTextureSampler;

void main(){
	vec3 normalizedNormal = normalize(normal);
	float diffuseIntensity = max(dot(normalizedNormal, normalize(vec3(1, 1, 1))), 0);
	//float pointIntensity = max(dot(normalizedNormal, normalize(vec3(0, lightY, 2) - position)), 0);//For point light
	//float dist = distance(vec3(0, lightY, 2), position);
	//pointIntensity = pointIntensity * 10 / (dist * dist);
	float ambientIntensity = 0.2f;

	vec2 glUV;
	glUV.x = UV.x;
	glUV.y = 1.0 - UV.y;
	color = texture2D(myTextureSampler, glUV).rgb * (ambientIntensity + diffuseIntensity);
}