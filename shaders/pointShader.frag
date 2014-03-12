#version 330

uniform sampler2D textureSampler;

smooth in vec3 position;
smooth in vec2 UV;
smooth in vec3 normal;

out vec3 color;

uniform vec3 pointLocation;

void main(){
	float pointIntensity = max(dot(normalize(normal), normalize(position - pointLocation)), 0);

	//color = texture2D(textureSampler, UV).rgb;
	//color *= pointIntensity;
	color = vec3(pointIntensity, pointIntensity, pointIntensity);
}