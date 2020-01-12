#version 400 core

layout (location = 0) in vec3 in_vPosition;	// the position variable has attribute position 0
layout (location = 1) in vec3 in_vColor;		// the color variable has attribute position 1

out vec3 color; // output a color to the fragment shader

void main()
{
	gl_Position = vec4(in_vPosition, 1.0);

	color = in_vColor;
}
