#ifndef VBO_H_INCLUDED
#define VBO_H_INCLUDED

#include <GL/glew.h>
#include <vector>

class VBO
{
    public:
        GLuint vbo;

        template<typename T>
        void bindBufferData(std::vector<T>& vertices)
        {
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), &vertices[0], GL_STATIC_DRAW);
        }
        void bindBufferDataV2(std::vector<Vector2>& vertices)
        {
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector2), &vertices[0], GL_STATIC_DRAW);
        }

        void deleteVbo(){glDeleteBuffers(1, &vbo);}

    protected:
    private:

};
#endif // VBO_H_INCLUDED
