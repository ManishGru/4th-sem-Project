#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include "glad.h"
std::string get_file_contents(const char *filename);

class Shader
{
public:
    GLuint ID;
    Shader(const char *vertexFile, const char *fragmentFile);

    GLuint compileShader(GLuint type, const std::string &source);
    void Activate();
    void Delete();
};

#endif