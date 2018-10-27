#pragma once

#include <GL/glew.h>
#include <Core_Engine/Shader.h>
#include <Math/Matrix.h>
#include <parsers/LoadTexture.h>
#include <typeinfo>
#include <vector>

class ShadowFrameBuffer
{
    public:
        ShadowFrameBuffer();

        void bindShader(const GLchar* vertex_shader, const GLchar* fragmentShader, const GLchar* geometryShader);
        void createDepthTexture2D();
        void createDepthCubeTexture();
        GLuint getDepthTexture();

        void bindDepthTexture2DToFBO(const GLuint &depth_texture);
        void bindDepthTexture2DToFBO();
        void bindDepthCubeTextureToFBO();

        bool initialize2D();
        bool initialize3D();

        void use(){
            glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
            glViewport(0,0,1024, 1024);
        }

        virtual ~ShadowFrameBuffer();
        Shader depthShader;
    protected:
    private:
        GLuint frameBuffer;
        GLuint depthTexture;
        GLuint depthCubeTexture;

        unsigned char* image;
};

