#version 450 core

layout (location = 5)
in vec3 pos;

out vec2 UV;

void main()
{
	gl_Position = vec4(pos, 1.0);
	UV = (pos.xy + vec2(1,1)/2.0);
}
