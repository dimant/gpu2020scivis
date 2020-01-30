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

uniform float fFragmentC;

uniform sampler2D texSampler;

void main()
{
	vec3 ambient = vLightColor * material.x;
	
	vec3 norm = normalize(normal);
	vec3 lightDirection = normalize(vLightPosition - fragmentPosition * fFragmentC);
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = material.y * diff * ambient;
	
	vec3 viewDirection = normalize(vCameraPosition - fragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.w);
	vec3 specular = material.z * spec * ambient;
	
	vec4 color = texture(texSampler, texCoord);
	vec4 light = vec4((ambient + diffuse + specular), 1.0f);
	frag_color = color * light;
}
