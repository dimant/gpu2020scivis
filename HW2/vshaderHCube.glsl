#version 440 core

layout (location = 0) in vec3 in_vPosition;
layout (location = 1) in vec2 in_vTexCoord;
layout (location = 2) in vec3 in_vNormal;
layout (location = 3) in vec3 in_vMaterial;

out vec2 texCoord;
out vec3 fragmentPosition;
out vec3 normal;
out vec3 material;

uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProj;
uniform mat3 mNormal;

void main()
{
	gl_Position = mProj * mView * mModel * vec4(in_vPosition, 1.0);

	texCoord = in_vTexCoord;
	fragmentPosition = vec3(mModel * vec4(in_vPosition, 1.0));
	normal = mNormal * in_vNormal;
	material = in_vMaterial;
}
