#include <Core_Engine/Mesh.h>

Mesh::Mesh()
{
}

Mesh::Mesh(const char* path, const int &face)
{
	OBJ_Loader obj;
	obj.loadOBJ(path, vertices, uvs, normals, face);
}

void Mesh::loadOBJfile(const char* path, const int &face)
{
    OBJ_Loader obj;
	obj.loadOBJ(path, vertices, uvs, normals, face);
}

void Mesh::init()
{
    indexVBO(vertices, normals, uvs, indices, m_vertices, m_normals, m_uvs);
    vbo.bindBufferData(vertices);
    tbo.bindBufferDataV2(uvs);
    nbo.bindBufferData(normals);
    ebo.bindBufferData(indices);
    vao.bindBufferData(vbo, ebo, nbo, tbo);

    for(int i = 0; i < m_vertices.size(); i++)
    {
        if(m_vertices[i].x > max_position.x)
            max_position.x = m_vertices[i].x;
        if(m_vertices[i].x < min_position.x)
            min_position.x = m_vertices[i].x;

        if(m_vertices[i].y > max_position.y)
            max_position.y = m_vertices[i].y;
        if(m_vertices[i].y < min_position.y)
            min_position.y = m_vertices[i].y;

        if(m_vertices[i].z > max_position.z)
            max_position.z = m_vertices[i].z;
        if(m_vertices[i].z < max_position.z)
            min_position.z = m_vertices[i].z;
    }
}

void Mesh::init(VBO& Vbo, VBO& Nbo, EBO& Ebo, VAO& Vao)
{
    //indexVBO(vertices, normals, indices, m_vertices, m_normals);
    Ebo.bindBufferData(indices);
    Vbo.bindBufferData(m_vertices);
    Nbo.bindBufferData(m_normals);
    //Vao.bindBufferData(Vbo, Ebo, Nbo);
}

void Mesh::clean()
{
    vertices.clear();
    uvs.clear();
    normals.clear();

    m_vertices.clear();
    m_uvs.clear();
    m_normals.clear();

    vbo.deleteVbo();
    vao.deleteVao();
    ebo.deleteEbo();
    nbo.deleteVbo();
}

void Mesh::init(VBO& vbo)
{
    //indexVBO(vertices, normals, indices, m_vertices, m_normals);
    vbo.bindBufferData(m_vertices);
}

void Mesh::init(EBO& ebo)
{
    //indexVBO(vertices, normals, indices, m_vertices, m_normals);
}

void Mesh::setShader(const char* vert, const char* frag, const char* geometry)
{
    shader.setShader(vert, frag, geometry);
}

void Mesh::scale(const GLfloat scalar)
{
    max_position = max_position * scalar;
    min_position = min_position * scalar;
    model.scale(scalar);
}

void Mesh::setColor(const float R, const float G, const float B)
{
    shader.use();
    uniColor = glGetUniformLocation(shader.Program, "overrideColor");
    rgb.x = R;
    rgb.y = G;
    rgb.z = B;
    glUniform3f(uniColor, rgb.x, rgb.y, rgb.z);
    glUseProgram(0);
}

void Mesh::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    Quaternion q(1, 0, 0, 0);
    q = q.get_local_rotation(angle, x, y, z) * q;
    model = q.get_quaternion_matrix() * model;
}

void Mesh::light(Vector3 light_position, Vector3 camera_position,
     Vector3 specular, Vector3 ambient, Vector3 diffuse, const float strength)
{
    shader.use();

    Vector3 lightColor = getColor();

    glUniform3f(glGetUniformLocation(shader.Program, "light.position"),
        light_position.x, light_position.y, light_position.z);
    glUniform3f(glGetUniformLocation(shader.Program, "viewPos"), camera_position.x, camera_position.y, camera_position.z);

    Vector3 diffuseColor = lightColor * Vector3(0.5f);
    Vector3 ambientColor = diffuseColor * Vector3(0.2f);
    glUniform3f(glGetUniformLocation(shader.Program, "light.ambient"),
        ambientColor.x, ambientColor.y, ambientColor.z);

    glUniform3f(glGetUniformLocation(shader.Program, "light.diffuse"),
        diffuseColor.x, diffuseColor.y, diffuseColor.z);

    glUniform3f(glGetUniformLocation(shader.Program, "light.specular"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(shader.Program, "material.ambient"), ambient.x, ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shader.Program, "material.diffuse"), diffuse.x, diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shader.Program, "material.specular"), specular.x, specular.y, specular.z);
    glUniform1f(glGetUniformLocation(shader.Program, "material.shine"), 32.0f);

    glUniform1f(glGetUniformLocation(shader.Program, "light.strength"), strength);

    glUniform1f(glGetUniformLocation(shader.Program, "light.constant"), 1.0f);
    glUniform1f(glGetUniformLocation(shader.Program, "light.linear"), 0.09f);
    glUniform1f(glGetUniformLocation(shader.Program, "light.quadratic"), 0.032f);

    glUseProgram(0);
}

void Mesh::spotlight(Vector3 light_position, Vector3 camera_position, Vector3 direction,
    Vector3 specular, Vector3 ambient, Vector3 diffuse,
    const float spotlight_length, const float spotlight_radius, const float strength)
{
    shader.use();

    Vector3 lightColor = getColor();

    glUniform3f(glGetUniformLocation(shader.Program, "light.position"),
        light_position.x, light_position.y, light_position.z);
    glUniform3f(glGetUniformLocation(shader.Program, "viewPos"),
        camera_position.x, camera_position.y, camera_position.z);

    GLuint spotLightDirID = glGetUniformLocation(shader.Program, "light.direction");
    GLuint spotLightCutOffID = glGetUniformLocation(shader.Program, "light.cutOff");
    GLuint spotLightOuterCutOffID = glGetUniformLocation(shader.Program, "light.outerCutOff");

    glUniform3f(spotLightDirID, direction.x, direction.y, direction.z);
    const float DEG2RAD = 3.141593f / 180.0f;
    glUniform1f(spotLightCutOffID, cos(DEG2RAD * spotlight_radius));
    glUniform1f(spotLightOuterCutOffID, cos(DEG2RAD * spotlight_length));

    Vector3 diffuseColor = lightColor * Vector3(0.5f);
    Vector3 ambientColor = diffuseColor * Vector3(0.2f);
    glUniform3f(glGetUniformLocation(shader.Program, "light.ambient"),
        ambientColor.x, ambientColor.y, ambientColor.z);

    glUniform3f(glGetUniformLocation(shader.Program, "light.diffuse"),
        diffuseColor.x, diffuseColor.y, diffuseColor.z);

    glUniform3f(glGetUniformLocation(shader.Program, "light.specular"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(shader.Program, "material.ambient"), 1.0f, 0.5f, 0.31f);
    glUniform3f(glGetUniformLocation(shader.Program, "material.diffuse"), 1.0f, 0.5f, 0.31f);
    glUniform3f(glGetUniformLocation(shader.Program, "material.specular"), 0.5f, 0.5f, 0.5f);
    glUniform1f(glGetUniformLocation(shader.Program, "material.shine"), 32.0f);

    glUniform1f(glGetUniformLocation(shader.Program, "light.constant"), 1.0f);
    glUniform1f(glGetUniformLocation(shader.Program, "light.linear"), 0.09f);
    glUniform1f(glGetUniformLocation(shader.Program, "light.quadratic"), 0.032f);

    glUseProgram(0);
}

void Mesh::move(GLfloat x, GLfloat y, GLfloat z)
{
    model.translate(x, y, z);
}

void Mesh::move(Vector3 pos)
{
    model.translate(pos);
}


void setTexture(Texture tex)
{
}
