#version 450 core

layout (location = 0)
in vec3 pos;
layout (location = 1)
in vec3 normal;

in vec2 texcoord;

out vec3 vertexColor;
out vec2 Texcoord;
out vec3 Normal;
out vec3 fragPos;

out vec3 reflected;
out vec3 refracted;
uniform vec3 cameraPos;

out vec4 shadowCoord;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
uniform vec3 overrideColor;

uniform mat4 depthBiasMatrix;

void main()
{
	Texcoord = texcoord;
	vertexColor = overrideColor;
	vec4 worldPosition = proj * view * model * vec4(pos, 1.0);
	gl_Position = worldPosition;
	fragPos = vec3(model * vec4(pos, 1.0f));
	Normal = mat3(transpose(inverse(model))) * normal;
	vec3 unitNormal = normalize(normal);

    vec3 vector = normalize(worldPosition.xyz - cameraPos);
	reflected = reflect(vector, unitNormal);
	refracted = refract(vector, unitNormal, 1.0f/1.33f);

	shadowCoord = depthBiasMatrix * vec4(pos, 1.0);
}
