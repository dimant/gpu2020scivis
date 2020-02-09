#version 440

out vec4 frag_color;

in vec3 fragmentPosition;

void main()
{
	vec4 color = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	frag_color = color;
}
