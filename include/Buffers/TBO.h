#ifndef TBO_H
#define TBO_H


class TBO
{
    public:
        GLuint tex;

        void bindBufferData()
        {
            GLint texAttrib = glGetAttribLocation(shader.Program, "texcoord");
            glEnableVertexAttribArray(texAttrib);
            glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (GLvoid*)0));
        }

    protected:
    private:
};

#endif // TBO_H
