#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"
#include <string>
#include <fstream>
#include <sstream>

enum
{
    VERTEX = 0, FRAGMENT = 1
};

class Shader
{
public:
    void parseShader(std::string filePath);
    void createShader();
    void compileShader();
    void parseCreateAndCompileShader(std::string filePath);
    void operator=(const Shader& shader);
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    std::string shaderFileName;
    GLuint programID;
    GLuint vertexShaderID;
    GLuint fragmentShaderID;
};

#endif // SHADER_H
