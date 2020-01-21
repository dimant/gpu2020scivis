#version 440 core

layout (location = 0) in vec3 in_vPosition;	// the position variable has attribute position 0
layout (location = 1) in vec3 in_vColor;		// the color variable has attribute position 1

out vec3 color; // output a color to the fragment shader

uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProj;

void main()
{
	// gl_Position = mProj * mView * mModel * vec4(in_vPosition, 1.0);

	gl_Position = mProj * mView * mModel * vec4(in_vPosition, 1.0);

	color = in_vColor;
}
