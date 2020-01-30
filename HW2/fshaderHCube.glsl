#version 440

out vec4 frag_color;

in vec2 texCoord;
in vec3 fragmentPosition;
in vec3 normal;

uniform vec4 vLightCoef; // x: ambient (ka), y: diffuse (kd), z: specular (ks), w: shinyness (s)
uniform vec3 vLightColor;
uniform vec3 vLightPosition;
uniform vec3 vCameraPosition;

uniform sampler2D texSampler;

void main()
{
	vec3 norm = normalize(normal);
	vec3 lightDirection = normalize(vLightPosition - fragmentPosition);
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = vLightCoef.y * diff * vLightColor;
	vec3 viewDirection = normalize(vCameraPosition - fragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), vLightCoef.w);
	vec3 specular = vLightCoef.z * spec * vLightColor;
	
	vec4 color = texture(texSampler, texCoord);
	vec4 light = vec4((vLightColor + diffuse + specular), 1.0f);
	frag_color = color * light;
}
