#version 440

out vec4 frag_color;

in vec3 color;

in vec3 normal;
in vec3 fragmentPosition;

uniform vec4 vLightCoef; // x: ambient (ka), y: diffuse (kd), z: specular (ks), w: shinyness (s)
uniform vec3 vLightColor;
uniform vec3 vLightPosition;
uniform vec3 vCameraPosition;

void main()
{
	vec3 norm = normalize(normal);
	vec3 lightDirection = normalize(vLightPosition - fragmentPosition);
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = diff * vLightColor;
	vec3 viewDirection = normalize(vCameraPosition - fragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), vLightCoef.w);
	vec3 specular = vLightCoef.z * spec * vLightColor;
	
	frag_color = vec4(color * (vLightColor + diffuse + specular), 1.0f);
}
