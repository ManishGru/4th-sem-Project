#include <iostream>
#include <stdlib.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "commonShader.hpp"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Cuboid
{
private:
    float El, Bi, Ech;

public:
    Cuboid(float, float, float);
    void drawCube(GLfloat *, GLfloat *);
    ~Cuboid();
};

Cuboid::Cuboid(float l, float b, float h)
{
    this->El = l;
    this->Bi = b;
    this->Ech = h;
}

Cuboid::~Cuboid()
{
}

void Cuboid::drawCube(GLfloat* vertex, GLfloat* index){
    
}
