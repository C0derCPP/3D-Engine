#version 450 core

layout (location = 0)
in vec3 position;
layout (location = 1)
in vec3 col;

out vec3 vertexColor;
out vec3 Texcoords;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
uniform vec3 overrideColor;

void main()
{
	vec4 pos = proj * view * model * vec4(position, 1.0f);
	vertexColor = overrideColor * col;
	gl_Position = pos;
	Texcoords = position;
}
