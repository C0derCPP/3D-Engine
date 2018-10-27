#ifndef TEXTURE_H
#define TEXTURE_H

#include "Shader.h"
#include "Math/Vector.h"
#include <parsers/LoadTexture.h>

class Texture
{
    public:
        Texture();
        ~Texture();

        void init(Shader& shader, Vector2& texcoords);
        void loadTexture(const char* path);

    protected:
    private:
};

#endif // TEXTURE_H
