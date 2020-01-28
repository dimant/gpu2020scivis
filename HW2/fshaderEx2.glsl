#version 440

out vec4 frag_color;

in vec3 color;
in vec2 texCoord;

uniform sampler2D texSampler;

void main()
{
    frag_color = texture(texSampler, texCoord);
}