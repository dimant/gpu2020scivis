#version 400 core

in vec3 in_vPosition;

void main()
{
	gl_Position = vec4(in_vPosition, 1.0);
}
