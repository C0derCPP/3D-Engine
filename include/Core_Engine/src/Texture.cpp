#include <Core_Engine/Texture.h>

Texture::Texture()
{
    //ctor
}

Texture::~Texture()
{
    //dtor
}

void Texture::init(Shader& shader, Vector2& texcoords)
{
    GLint uniTex = glGetUniformLocation(shader.Program, "Texcoord");
    glUniform2f(uniTex, texcoords.y, texcoords.y);
}

void Texture::loadTexture(const char* path)
{
    LoadTexture ldt;
    ldt.loadTexture(path);
}
