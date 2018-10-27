#version 450 core

layout (location = 0)
in vec3 pos;

uniform mat4 depthMVP;

void main()
{
	vec4 worldPosition = depthMVP * vec4(pos, 1.0);
	gl_Position = worldPosition;
}

