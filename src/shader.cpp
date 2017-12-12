#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    //1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFIle;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFIle.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFIle.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        //Read file buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFIle.rdbuf();
        //close file handlers
        vShaderFile.close();
        fShaderFIle.close();
        //convert streams into strings
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    //2. Compile the shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    //Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    //print compile errors
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    //print compile errors
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Shader program
    Shader::ID = glCreateProgram();
    glAttachShader(Shader::ID, vertex);
    glAttachShader(Shader::ID, fragment);
    glLinkProgram(Shader::ID);
    //Get linking errors
    glGetProgramiv(Shader::ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(Shader::ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void Shader::use() {
    glUseProgram(Shader::ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4 value) const
{
    unsigned int valueLoc = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(valueLoc, 1, GL_FALSE, glm::value_ptr(value));
}

