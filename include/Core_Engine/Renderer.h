#pragma once

#include <GL/glew.h>

#include "Mesh.h"
#include "Camera.h"

class Renderer
{
    public:
        Renderer();
        ~Renderer();

        void setup();
        void prepare(Camera& camera);

        void render(Mesh& mesh){ drawEBO(mesh); }

        template<typename first, typename ... t_mesh>
        void render3D(first& mesh, t_mesh& ... rest)
        {
            drawEBO(mesh);
            render(rest...);
        }
        template<typename first, typename ... t_mesh>
        void render2D(first& mesh, t_mesh& ... rest)
        {
            drawEBO(mesh);
            render(rest...);
        }

        void drawEBO(Mesh& mesh, VAO& Vao);
        void drawEBO(Mesh& mesh);
        void drawVBO(Mesh& mesh);
        void drawVBO2D(Mesh& mesh);

        void draw(const int& vertices);
        void initView3D(Mesh& mesh);
        void initView2D(Mesh& mesh);

    protected:
    private:
        int vertices;
        bool boolean;
        Matrix4 view;
        Matrix4 proj;
        Matrix4 ortho;
        Matrix4 model;

        GLuint uniProj;
        GLint uniView;
        GLint uniModel;

        Vector3 pos, camera_position;
};
