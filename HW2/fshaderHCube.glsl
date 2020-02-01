#version 440

out vec4 frag_color;

in vec2 texCoord;
in vec3 fragmentPosition;
in vec3 normal;
in vec4 material;

//uniform vec4 vLightCoef; // x: ambient (ka), y: diffuse (kd), z: specular (ks), w: shinyness (s)
uniform vec3 vLightColor;
uniform vec3 vLightPosition;
uniform vec3 vCameraPosition;

// x: constant, y: linear, z: quadratic, w: enabled
uniform vec4 vLightAttenuation;

// used to switch betwen directional and point light
uniform float fFragmentC;

uniform sampler2D texSampler;

void main()
{
	// ambient
	vec3 ambient = vLightColor * material.x;
	
	// diffuse
	vec3 norm = normalize(normal);
	vec3 lightDirection = normalize(vLightPosition - fragmentPosition * fFragmentC);
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = material.y * diff * ambient;
	
	// specular
	vec3 viewDirection = normalize(vCameraPosition - fragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.w);
	vec3 specular = material.z * spec * ambient;

	// attenuation
	float d = length(vLightPosition - fragmentPosition) * vLightAttenuation.w;
	float attenuation = 1.0 / (
		vLightAttenuation.x +
		vLightAttenuation.y * d +
		vLightAttenuation.z * (d * d));

	// texture
	vec4 color = texture(texSampler, texCoord);

	// UPL
	vec4 light = vec4((
		ambient * attenuation +
		diffuse * attenuation +
		specular * attenuation
	), 1.0f);

	frag_color = color * light;
}
