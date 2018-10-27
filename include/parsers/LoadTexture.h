#pragma once

#include <GL/glew.h>
#include <vector>
#include <SOIL.h>

typedef class LoadTexture
{
    public:
        GLuint loadTexture(const GLchar *path);
        GLuint loadCubeMap(std::vector<const GLchar *> faces);
} loadTex;

