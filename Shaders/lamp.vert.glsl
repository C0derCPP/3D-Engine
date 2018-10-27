#version 450 core

layout (location = 0)
in vec3 pos;
layout (location = 1)
in vec3 col;

in vec2 texcoord;

out vec3 vertexColor;
out vec2 Texcoord;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
uniform vec3 overrideColor;

void main()
{
	Texcoord = texcoord;
	vertexColor = overrideColor;
	gl_Position = proj * view * model * vec4(pos, 1.0);
}
