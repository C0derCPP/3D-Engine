#ifndef VAO_H_INCLUDED
#define VAO_H_INCLUDED

#include <GL/glew.h>
#include <vector>

#include "VBO.h"
#include "EBO.h"


class VAO
{
    public:
        GLuint vao;

        void enable()
        {
            glBindVertexArray(vao);
        }
        void disable()
        {
            glBindVertexArray(0);
        }

        void bindBufferData(VBO& vbo, EBO& ebo, VBO& nbo, VBO& tbo)
        {
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vbo.vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, nbo.vbo);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, tbo.vbo);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.ebo);
        }

        void deleteVao(){glDeleteVertexArrays(1, &vao);}

    protected:
    private:

};

#endif // VAO_H_INCLUDED
