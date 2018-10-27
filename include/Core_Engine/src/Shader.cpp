#include <Core_Engine/Shader.h>

Shader::Shader()
{
    //ctor
}

Shader::Shader(std::string vertexShader, std::string fragmentShader, std::string geometryShader)
{
    Program = glCreateProgram();
    if(!vertexShader.empty())
    {
        VertexShader = vertexShader;
        vertexShader = loadFileContent(vertexShader);
        compileVertexShader(vertexShader.c_str());
        glAttachShader(Program, m_vertexShader);
    }

    if(!fragmentShader.empty())
    {
        FragmentShader = fragmentShader;
        fragmentShader = loadFileContent(fragmentShader);
        compileFragmentShader(fragmentShader.c_str());
        glAttachShader(Program, m_fragmentShader);
    }

    if(!geometryShader.empty())
    {
        GeometryShader = geometryShader;
        geometryShader = loadFileContent(geometryShader);
        compileGeometryShader(geometryShader.c_str());
        glAttachShader(Program, m_geometryShader);
    }

	glLinkProgram(Program);

    GLint succes;
	GLchar infoLog[512];
	glGetProgramiv(Program, GL_LINK_STATUS, &succes);
	if(!succes)
	{
		glGetProgramInfoLog(Program, 512, nullptr, infoLog);
		std::cout << "failed to link program: " << infoLog << std::endl;
	}
}

void Shader::setShader(std::string vertexShader, std::string fragmentShader, std::string geometryShader)
{
    Program = glCreateProgram();
    if(!vertexShader.empty())
    {
        VertexShader = vertexShader;
        vertexShader = loadFileContent(vertexShader);
        compileVertexShader(vertexShader.c_str());
        glAttachShader(Program, m_vertexShader);
    }

    if(!fragmentShader.empty())
    {
        FragmentShader = fragmentShader;
        fragmentShader = loadFileContent(fragmentShader);
        compileFragmentShader(fragmentShader.c_str());
        glAttachShader(Program, m_fragmentShader);
    }

    if(!geometryShader.empty())
    {
        GeometryShader = geometryShader;
        geometryShader = loadFileContent(geometryShader);
        compileGeometryShader(geometryShader.c_str());
        glAttachShader(Program, m_geometryShader);
    }

	glLinkProgram(Program);

    GLint succes;
	GLchar infoLog[512];
	glGetProgramiv(Program, GL_LINK_STATUS, &succes);
	if(!succes)
	{
		glGetProgramInfoLog(Program, 512, nullptr, infoLog);
		std::cout << "failed to link program: " << infoLog << std::endl;
	}
}

//compile the vertex shader
GLuint Shader::compileVertexShader(const GLchar* vertexShaderText)
{
    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(m_vertexShader, 1, &vertexShaderText, nullptr);
	glCompileShader(m_vertexShader);

	GLint succes;
	GLchar infoLog[512];
	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &succes);
	if(!succes)
	{
		glGetShaderInfoLog(m_vertexShader, 512, nullptr, infoLog);
		std::cout << "(" << VertexShader << ")" << "failed to compile: " << infoLog << std::endl;
	}
	else
        std::cout << "(" << VertexShader << ")" << "compiled" << std::endl;
}

//compile the fragment shader
GLuint Shader::compileFragmentShader(const GLchar* fragmentShaderText)
{
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(m_fragmentShader, 1, &fragmentShaderText, nullptr);
	glCompileShader(m_fragmentShader);

    GLint succes;
	GLchar infoLog[512];
	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(m_fragmentShader, 512, nullptr, infoLog);
		std::cout << "(" << FragmentShader << ")" << "failed to compile: " << infoLog << std::endl;
	}
	else
        std::cout << "(" << FragmentShader << ")" << "compiled" << std::endl;
}

//compile the geometry shader
GLuint Shader::compileGeometryShader(const GLchar* geometryShaderText)
{
    m_geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

    glShaderSource(m_geometryShader, 1, &geometryShaderText, nullptr);
	glCompileShader(m_geometryShader);

    GLint succes;
	GLchar infoLog[512];
	glGetShaderiv(m_geometryShader, GL_COMPILE_STATUS, &succes);
	if(!succes)
	{
		glGetShaderInfoLog(m_geometryShader, 512, nullptr, infoLog);
		std::cout << "(" << GeometryShader << ")" << "failed to compile: " << infoLog << std::endl;
	}
	else
        std::cout << "(" << GeometryShader << ")" << "compiled" << std::endl;
}

std::string Shader::loadFileContent(const std::string filepath)
{
    std::ifstream file(filepath);
	std::stringstream sstream;

	if(!file.is_open())
	{
		std::cout << "could not find file: " << filepath << std::endl;
	}

	sstream << file.rdbuf();
	return sstream.str();
}
