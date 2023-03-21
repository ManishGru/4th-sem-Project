#ifndef _CUBE_CLASS_H
#define _CUBE_CLASS_H
#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "Camera.h"
#include "Texture.h"
class Cube
{
public:
    GLfloat vertices[16 * 3] = {
        0.0f, 0.0f, 0.0f, // 0
        0.0f, 0.0f, 1.0f, // 1
        1.0f, 0.0f, 1.0f, // 2
        1.0f, 0.0f, 0.0f, // 3
        0.0f, 1.0f, 0.0f, // 4
        0.0f, 1.0f, 1.0f, // 5
        1.0f, 1.0f, 1.0f, // 6
        1.0f, 1.0f, 0.0f, // 7
        0.0f, 0.0f, 0.0f, // 8
        0.0f, 0.0f, 1.0f, // 9
        1.0f, 0.0f, 1.0f, // 10
        1.0f, 0.0f, 0.0f, // 11
        0.0f, 1.0f, 0.0f, // 12
        0.0f, 1.0f, 1.0f, // 13
        1.0f, 1.0f, 1.0f, // 14
        1.0f, 1.0f, 0.0f, // 15
    };

    GLfloat normal[16 * 3] = {
        -1.0f, -1.0f, -1.0f,//1
        -1.0f, -1.0f, 1.0f,   //2
        1.0f, -1.0f, 1.0f,//3
        1.0f, -1.0f, -1.0f,      //4
        -1.0f, 1.0f, -1.0f,//5
        -1.0f, 1.0f, 1.0f,//6
        1.0f, 1.0f, 1.0f,//7
        1.0f, 1.0f, -1.0f,//8
        -1.0f, -1.0f, -1.0f,//9
        -1.0f, -1.0f, 1.0f,//10
        1.0f, -1.0f, 1.0f,//11
        1.0f, -1.0f, -1.0f,//12
        -1.0f, 1.0f, -1.0f,//13
        -1.0f, 1.0f, 1.0f,//14
        1.0f, 1.0f, 1.0f,//15
        1.0f, 1.0f, -1.0f};//16
    GLfloat texCoords[16 * 2] = {
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f};
    GLuint indices[6 * 2 * 3] = {
        0, 4, 1,    // left
        1, 4, 5,    // left
        0, 4, 3,    // bottom
        4, 3, 7,    // bottom
        2, 3, 6,    // left
        3, 6, 7,    // left
        1, 2, 6,    // top
        1, 5, 6,    // top
        12, 13, 14, // back
        12, 14, 15, // back
        8, 10, 11,  // front
        9, 8, 10    // front
    };

    GLfloat width, breadth, height;
    GLfloat location[3];
    VAO *cubeVAO;
    VBO *cubeVBO;
    VBO *texVBO;
    VBO *normalVBO;
    EBO *cubeEBO;
    Texture *texture;
    Cube(){}
    Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat b, GLfloat h, bool scaleTex);
    void linkAttribs();
    void Unbind();
    void linkTexture(Texture &texture);
    void render();
    void Delete();
    void sourceRender();
    void sourceLink();
};
#endif