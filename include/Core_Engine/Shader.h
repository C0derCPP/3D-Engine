#pragma once

#include <iostream>
#include <GL/glew.h>
#include <glfw3.h>
#include <string>
#include <sstream>
#include <fstream>

class Shader
{
    public:
        GLuint Program;
        Shader();

        Shader(std::string vertexShader, std::string fragmentShader, std::string geometryShader);
        void setShader(std::string vertexShader, std::string fragmentShader, std::string geometryShader);
        void setVertexShader(std::string vertexShader);
        void setFragmentShader(std::string fragmentShader);
        void setGeometryShader(std::string geometryShader);

        void use();

    protected:
    private:
        GLuint compileVertexShader(const GLchar* vertexShaderText);
        GLuint compileFragmentShader(const GLchar* fragmentShaderText);
        GLuint compileGeometryShader(const GLchar* geometryShadetText);

        std::string loadFileContent(const std::string filepath);
        std::string VertexShader;
        std::string FragmentShader;
        std::string GeometryShader;

        GLuint m_vertexShader;
        GLuint m_fragmentShader;
        GLuint m_geometryShader;

};

inline void Shader::use()
{
    glUseProgram(Program);
}
