#version 440 core

layout (location = 0) in vec3 in_vPosition;

out vec3 fragmentPosition;

uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProj;
uniform mat3 mNormal;

void main()
{
	gl_Position = mProj * mView * mModel * vec4(in_vPosition, 1.0);

	fragmentPosition = vec3(mModel * vec4(in_vPosition, 1.0));
}
