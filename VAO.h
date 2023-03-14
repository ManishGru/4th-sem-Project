#pragma once
#include "VBO.h"
class VAO
{
public:
    GLuint ID;

    VAO()
    {
        glGenVertexArrays(1, &ID);
    }

    void LinkAttrib(VBO vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
    {
        vbo.Bind();
        glVertexAttribPointer(layout, numComponents, type,GL_FALSE, 0, offset);
        glEnableVertexAttribArray(layout);
        vbo.UnBind();
    }

    void Bind(){
        glBindVertexArray(ID);
    }

    void UnBind()
    {
        glBindVertexArray(0);
    }

    void Delete()
    {
    glDeleteVertexArrays(1, &ID);
    }
};