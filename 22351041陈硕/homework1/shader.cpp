#include "shader.h"
//std
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//lib
#define GLEW_STATIC
#include <glad/glad.h>

void Shader::checkCompileErrors(unsigned int ID, std::string type)
{
    int success;
    char infoLog[512];

    if (type != "PROGRAM")
    {
        glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(ID, 512, NULL, infoLog);
            std::cout << "EOORO::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ��֤ifstream��������׳��쳣
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // ���ļ�
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        // ��ȡ�ļ��Ļ������ݵ���������
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // ��������ת��Ϊstring
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        // ��stringת��ΪOpenGL�ܹ�ʶ���const char*����
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;

        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        // fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // ������shader����
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        //�ڱ��롢link��֮��ɾ��shader
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    catch (std::exception& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

