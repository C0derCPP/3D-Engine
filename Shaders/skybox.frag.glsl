#version 450 core

in vec3 vertexColor;
in vec3 Texcoords;
out vec4 outcolor;

uniform samplerCube skybox;

void main()
{
	outcolor = texture(skybox, Texcoords);
}
