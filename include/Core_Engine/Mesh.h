#pragma once

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <glfw3.h>
#include <cmath>

#include <parsers/OBJ_Loader.h>
#include "Buffers/VBO.h"
#include "Buffers/VAO.h"
#include "Buffers/EBO.h"
#include "Shader.h"
#include "Texture.h"
#include <parsers/LoadTexture.h>
#include <parsers/VBOindexer.h>
#include "Math/Matrix.h"
#include "Math/Quaternion.h"
#include "Camera.h"

class Mesh
{
    public:
        std::vector<Vector3> m_vertices;
        std::vector<Vector2> m_uvs;
        std::vector<Vector3> m_normals;
        std::vector<unsigned short> indices;
        Shader shader;

        VAO vao;
        GLuint uniColor;

        Mesh();

        Mesh(const char* path, const int &face);
        void loadOBJfile(const char* path, const int &face);
        void init();
        void init(VBO& Vbo, VBO& Nbo, EBO& Ebo, VAO& Vao);
        void init(VBO& vbo);
        void init(EBO& ebo);
        void clean();

        void setShader(const char* vert, const char* frag, const char* geometry);
        void setShader(Shader shader_) { shader = shader_; };
        void scale(const GLfloat scalar);
        void setColor(const float r, const float g, const float b);
        void setTexture(Texture tex);
        void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
        void move(GLfloat x, GLfloat y, GLfloat z);
        void move(Vector3 pos);

        void light(Vector3 light_position, Vector3 camera_position,
                Vector3 specular, Vector3 ambient, Vector3 diffuse, const float strength);

        void spotlight(Vector3 light_position, Vector3 camera_position, Vector3 direction,
                Vector3 specular, Vector3 ambient, Vector3 diffuse,
                const float spotlight_length, const float spotlight_radius, const float strength);

        Matrix4 getModelMatrix(){ return model; }
        Vector3 getPosition() { return model * Vector3(0, 0, 0); }
        Vector3 getColor() { return rgb; }
        Vector3 getMaxPosition(){ return max_position; };
        Vector3 getMinPosition(){ return min_position; };

        int operator+(const Mesh &mesh){ return m_vertices.size() + mesh.m_vertices.size(); }
        std::vector<Vector3> vertices;

    protected:
    private:
        Matrix4 model;
        Vector3 max_position;
        Vector3 min_position;

        Vector3 rgb;

        VBO vbo;
        EBO ebo;
        VBO nbo;
        VBO tbo;

        std::vector<Vector2> uvs;
        std::vector<Vector3> normals;
};
