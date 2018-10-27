#version 450 core

in vec4 fragPos;

uniform vec3 ligtPos;
uniform float far_plane;

void main()
{
    float light_distance = length(fragPos.xyz - ligtPos);

    ligt_distance = light_distance / far_plane;

    gl_fragDepth = light_distance;
}
