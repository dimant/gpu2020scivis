#version 440

out vec4 frag_color;

in vec2 texCoord;
in vec3 fragmentPosition;
in vec3 normal;
in vec3 material;

//uniform vec4 vLightCoef; // x: ambient (ka), y: diffuse (kd), z: specular (ks), w: shinyness (s)
uniform vec3 vLightColor;

// Light.cpp ensures that in directional light mode, the vector is a direction
// from _target to _position
uniform vec3 vLightPosition;
uniform vec3 vLightDirection;

uniform vec3 vCameraPosition;

// x: constant, y: linear, z: quadratic, w: enabled
uniform vec4 vLightAttenuation;
uniform float fLightShininess;
uniform float fSpotEpsilon;
uniform float fSpotCosTheta;

// used to switch betwen directional and point light
uniform float fEnableDirectionalLight;

uniform sampler2D texSampler;

vec4 light()
{
	// ambient
	vec3 ambient = vLightColor * material.x;
	
	// diffuse
	vec3 norm = normalize(normal);
	vec3 lightIncidence = normalize(vLightPosition - fragmentPosition * fEnableDirectionalLight);
	float diff = max(dot(norm, lightIncidence), 0.0);
	vec3 diffuse = material.y * diff * ambient;

	// specular
	vec3 viewDirection = normalize(vCameraPosition - fragmentPosition);
	vec3 reflectDirection = reflect(-lightIncidence, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), fLightShininess);
	vec3 specular = material.z * spec * ambient;

	// attenuation
	float d = length(vLightPosition - fragmentPosition) * vLightAttenuation.w;
	float attenuation = 1.0 / (
		vLightAttenuation.x +
		vLightAttenuation.y * d +
		vLightAttenuation.z * (d * d));

	// spot
	float cosphi = dot(vLightDirection, lightIncidence);
	float falloff = pow(cosphi, fSpotEpsilon);
	float spot = step(fSpotCosTheta, cosphi) * falloff;

	// UPL
	return vec4((
		ambient * attenuation +
		diffuse * attenuation * spot +
		specular * attenuation * spot
	), 1.0f);
}

void main()
{
	// texture
	vec4 color = texture(texSampler, texCoord);

	frag_color = color * light();
}
