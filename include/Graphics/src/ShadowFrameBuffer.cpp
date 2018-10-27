#include "ShadowFrameBuffer.h"

ShadowFrameBuffer::ShadowFrameBuffer()
{
    frameBuffer = 0;
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    mat4x4 shadowProjection = shadowProjection.perspective(90.0f, 1.0f, 1.0f, 25.0f);
    Vector3 lightpos;
    mat4x4 mat;
    std::vector<mat4x4> shadowTransformation;
    shadowTransformation.push_back(shadowProjection * mat.lookAt
    (lightpos, lightpos + Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)));
    shadowTransformation.push_back(shadowProjection * mat.lookAt
    (lightpos, lightpos + Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f)));
    shadowTransformation.push_back(shadowProjection * mat.lookAt
    (lightpos, lightpos + Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)));
    shadowTransformation.push_back(shadowProjection * mat.lookAt
    (lightpos, lightpos + Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f)));
    shadowTransformation.push_back(shadowProjection * mat.lookAt
    (lightpos, lightpos + Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f)));
    shadowTransformation.push_back(shadowProjection * mat.lookAt
    (lightpos, lightpos + Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, -1.0f, 0.0f)));
}

ShadowFrameBuffer::~ShadowFrameBuffer()
{
    glDeleteFramebuffers(1, &frameBuffer);
}

void ShadowFrameBuffer::createDepthTexture2D()
{
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
}

GLuint ShadowFrameBuffer::getDepthTexture()
{
    return depthTexture;
}

void ShadowFrameBuffer::bindDepthTexture2DToFBO()
{
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);
}

void ShadowFrameBuffer::bindDepthTexture2DToFBO(const GLuint &depth_texture)
{
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_texture, 0);
}

void ShadowFrameBuffer::bindShader(const GLchar* vertex_shader, const GLchar* fragmentShader, const GLchar* geometryShader)
{
    depthShader.setShader(vertex_shader, fragmentShader, geometryShader);
}

void ShadowFrameBuffer::createDepthCubeTexture()
{
    int width = 1024, height = 1024;

    glGenTextures(1, &depthCubeTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeTexture);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    for(unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
            width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }
}

void ShadowFrameBuffer::bindDepthCubeTextureToFBO()
{
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubeTexture, 0);
}

bool ShadowFrameBuffer::initialize2D()
{
    createDepthCubeTexture();
    bindDepthTexture2DToFBO();
    glDrawBuffer(GL_NONE);
    bindShader("resources/Shaders/shadow.vert.glsl", "resources/Shaders/shadow.frag.glsl", "");

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
        std::cerr << "ShadowFrameBuffer: " << "failed to initialize framebuffer" << std::endl;
        return false;
    }
}

bool ShadowFrameBuffer::initialize3D()
{
    createDepthCubeTexture();
    bindDepthCubeTextureToFBO();
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    bindShader("resources/Shaders/shadow.vert.glsl", "resources/Shaders/shadow.frag.glsl", "resources/Shaders/shadow.g.glsl");

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
        std::cerr << "ShadowFrameBuffer: " << "failed to initialize framebuffer" << std::endl;
        return false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
