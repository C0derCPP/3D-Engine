#ifndef TEXT2D_H
#define TEXT2D_H

#include <vector>
#include <cstring>

#include <parsers/LoadTexture.h>
#include <Math/Matrix.h>
#include <Math/Vector.h>
#include <Core_Engine/Shader.h>

class Text2D
{
    public:
        void initText(const char* texturePath)
        {
            LoadTexture load;
            Text2DTextureID = load.loadTexture(texturePath);

            glGenBuffers(1, &Text2DVertexBufferID);
            glGenBuffers(1, &Text2DUVBufferID);

            Text2DShaderID.setShader("resources/Shaders/TextShader.vert.glsl", "resources/Shaders/TextShader.frag.glsl", "");
            Text2DUniformID = glGetUniformLocation(Text2DShaderID.Program, "myTextureSampler");
        }
        void printText(const char* text, const int x, const int y, const int size)
        {
            unsigned int length = strlen(text);

            for(unsigned int i = 0; i < length; i++)
            {
                Vector2 vertex_up_left    =         Vector2(x + i * size, y + size);
                Vector2 vertex_up_right   =  Vector2(x + i * size + size, y + size);
                Vector2 vertex_down_right =               Vector2(x+i*size+size, y);
                Vector2 vertex_down_left  =                    Vector2(x+i*size, y);

                vertices.push_back(vertex_up_left);
                vertices.push_back(vertex_down_left);
                vertices.push_back(vertex_up_right);

                vertices.push_back(vertex_down_right);
                vertices.push_back(vertex_up_right);
                vertices.push_back(vertex_down_left);

                char character = text[i];
                float uv_x = (character%16)/16.0f;
                float uv_y = (character/16)/16.0f;

                Vector2 uv_up_left     = Vector2                          (uv_x, uv_y);
                Vector2 uv_up_right    = Vector2               (uv_x+1.0f/16.0f, uv_y);
                Vector2 uv_down_right  = Vector2(uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f));
                Vector2 uv_down_left   = Vector2           (uv_x, (uv_y + 1.0f/16.0f));

                uvs.push_back(uv_up_left);
                uvs.push_back(uv_down_left);
                uvs.push_back(uv_up_right);

                uvs.push_back(uv_down_right);
                uvs.push_back(uv_up_right);
                uvs.push_back(uv_down_left);
            }
            glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector2), &vertices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
            glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(Vector2), &uvs[0], GL_STATIC_DRAW);

            Text2DShaderID.use();

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, Text2DTextureID);
            glUniform1i(Text2DUniformID, 0);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glDrawArrays(GL_TRIANGLES, 0, vertices.size());

            glDisable(GL_BLEND);

            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
        }
        void cleanText()
        {
            glDeleteBuffers(1, &Text2DVertexBufferID);
            glDeleteBuffers(1, &Text2DUVBufferID);

            glDeleteTextures(1, &Text2DTextureID);

            glDeleteProgram(Text2DShaderID.Program);
        }

    protected:
    private:
        std::vector<Vector2> vertices;
        std::vector<Vector2> uvs;

        unsigned int Text2DTextureID;
        unsigned int Text2DVertexBufferID;
        unsigned int Text2DUVBufferID;
        unsigned int Text2DUniformID;

        Shader Text2DShaderID;
};

#endif // TEXT2D_H
