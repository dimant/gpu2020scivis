#version 440

out vec4 frag_color;

in vec2 texCoord;

//uniform vec3 vCameraPosition;

uniform sampler2D texSampler;

void main()
{
    frag_color = texture(texSampler, texCoord);
}
