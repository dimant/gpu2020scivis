#version 440 core

layout (location = 0) in vec3 in_vPosition;
layout (location = 1) in vec2 in_vTexCoord;
//layout (location = 2) in vec3 in_vNormal;

out vec2 texCoord;
out vec3 fragmentPosition;

uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProj;

void main()
{
	gl_Position = mProj * mView * mModel * vec4(in_vPosition, 1.0);

	texCoord = in_vTexCoord;
	fragmentPosition = vec3(mModel * vec4(in_vPosition, 1.0));
}
