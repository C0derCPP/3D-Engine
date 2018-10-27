#include <Core_Engine/Renderer.h>

Renderer::Renderer()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(1);
    glEnable(GL_STENCIL_TEST);
    const float DEG2RAD = 3.141593f / 180.0f;
    proj = proj.perspective(45, float(700 / 600), 1.0f, 1000.0f);
    ortho = ortho.orthogonal(0, 700, 0, 600, 1, 1000);
}

void Renderer::initView3D(Mesh& mesh)
{
    model = mesh.getModelMatrix();
    uniProj  = glGetUniformLocation(mesh.shader.Program, "proj");
    uniView  = glGetUniformLocation(mesh.shader.Program, "view");
    uniModel = glGetUniformLocation(mesh.shader.Program, "model");
    glUniformMatrix4fv(uniProj,  1, GL_FALSE, proj.get());
    glUniformMatrix4fv(uniView,  1, GL_FALSE, view.get());
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, model.get());
    glUniform3f(mesh.uniColor, mesh.getColor().x, mesh.getColor().y, mesh.getColor().z);
}

void Renderer::initView2D(Mesh& mesh)
{
    model = mesh.getModelMatrix();
    uniProj  = glGetUniformLocation(mesh.shader.Program, "proj");
    uniView  = glGetUniformLocation(mesh.shader.Program, "view");
    uniModel = glGetUniformLocation(mesh.shader.Program, "model");
    glUniformMatrix4fv(uniProj,  1, GL_FALSE, ortho.get());
    glUniformMatrix4fv(uniView,  1, GL_FALSE, view.get());
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, model.get());
    glUniform3f(mesh.uniColor, mesh.getColor().x, mesh.getColor().y, mesh.getColor().z);
}

Renderer::~Renderer()
{
    //dtor
}

void Renderer::prepare(Camera& camera)
{
    view = camera.getViewMatrix();
    camera_position = camera.getPosition();
}

void Renderer::drawEBO(Mesh& mesh, VAO& Vao)
{
    //draw mesh
    mesh.shader.use();
    initView3D(mesh);
    Vao.enable();
    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_SHORT, (GLvoid*)0);
    Vao.disable();
}
void Renderer::drawEBO(Mesh& mesh)
{
    pos = mesh.getPosition();
    //draw mesh
    mesh.shader.use();
    initView3D(mesh);
    mesh.vao.enable();
    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_SHORT, (GLvoid*)0);
    mesh.vao.disable();
    glUseProgram(0);
}

void Renderer::drawVBO(Mesh& mesh)
{
    pos = mesh.getPosition();
    //draw mesh
    mesh.shader.use();
    initView3D(mesh);
    mesh.vao.enable();
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertices.size());
    mesh.vao.disable();
    glUseProgram(0);
}

void Renderer::drawVBO2D(Mesh& mesh)
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);
    pos = mesh.getPosition();
    //draw mesh
    mesh.shader.use();
    initView2D(mesh);
    mesh.vao.enable();
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertices.size());
    mesh.vao.disable();
    glUseProgram(0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(1);
}

void Renderer::draw(const int& vertices)
{
    //draw mesh
    glDrawArrays(GL_TRIANGLES, 0, vertices);
}

