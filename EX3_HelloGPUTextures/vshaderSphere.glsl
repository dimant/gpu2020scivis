#version 440 core

layout (location = 0) in vec3 in_vPosition;
layout (location = 1) in vec3 in_vNormal;
layout (location = 2) in vec3 in_vColor;

out vec3 color; // output a color to the fragment shader

uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProj;

void main()
{
	gl_Position = mProj * mView * mModel * vec4(in_vPosition, 1.0);

	color = in_vColor;
}
