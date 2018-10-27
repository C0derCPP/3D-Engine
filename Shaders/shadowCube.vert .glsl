#version 450 core

layout (location = 0)
in vec3 pos;

uniform mat4 model;

void main()
{
	vec4 worldPosition = model * vec4(pos, 1.0);
	gl_Position = worldPosition;
}

