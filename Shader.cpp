#include "Shader.h"
#include <malloc.h>
#include <iostream>

void Shader::parseShader(std::string filePath)
{
    std::ifstream file(filePath);
    std::string line;
    int shaderType;
    std::stringstream ss[2];

    while(getline(file, line))
    {
        if(line.find("#vertex") != std::string::npos)
        {
            shaderType = VERTEX;
        }
        else if(line.find("#fragment") != std::string::npos)
        {
            shaderType = FRAGMENT;
        }
        else
        {
            ss[shaderType] << line << "\n";
        }
    }
    vertexShaderSource = ss[VERTEX].str();
    fragmentShaderSource = ss[FRAGMENT].str();
}

void Shader::createShader()
{
    programID = glCreateProgram();
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
}

void Shader::compileShader()
{
    const char* vertexSourcePointer = vertexShaderSource.c_str();
    const char* fragmentSourcePointer = fragmentShaderSource.c_str();
    glShaderSource(vertexShaderID, 1, &vertexSourcePointer, nullptr);
    glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, nullptr);
    glCompileShader(vertexShaderID);
    glCompileShader(fragmentShaderID);

    int result;
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int lentgh;
        glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &lentgh);
        char* message = (char*)_alloca(lentgh * sizeof(char));
        glGetShaderInfoLog(vertexShaderID, lentgh, &lentgh, message);
        std::cout << message;
    }

    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int lentgh;
        glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &lentgh);
        char* message = (char*)_alloca(lentgh * sizeof(char));
        glGetShaderInfoLog(fragmentShaderID, lentgh, &lentgh, message);
        std::cout << message;
    }

    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
}

void Shader::parseCreateAndCompileShader(std::string filePath)
{
    parseShader(filePath);
    createShader();
    compileShader();
}

void Shader::operator=(const Shader& shader)
{
    vertexShaderSource = shader.vertexShaderSource;
    fragmentShaderSource = shader.fragmentShaderSource;
    shaderFileName = shader.shaderFileName;
    programID = shader.programID;
    vertexShaderID = shader.vertexShaderID;
    fragmentShaderID = shader.fragmentShaderID;
}
