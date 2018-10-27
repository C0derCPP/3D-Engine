#ifndef EBO_H_INCLUDED
#define EBO_H_INCLUDED

#include <GL/glew.h>
#include <vector>

class EBO
{
    public:
        GLuint ebo;

        void bindBufferData(std::vector<unsigned short>& indices)
        {
            glGenBuffers(1, &ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
        }

        void deleteEbo(){glDeleteBuffers(1, &ebo);}

    protected:
    private:

};

#endif // EBO_H_INCLUDED
