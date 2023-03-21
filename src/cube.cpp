#include "../inc/cube.h"
Cube::Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat b, GLfloat h, bool scaleTex)
{
    width = w;
    breadth = b;
    height = h;
    location[0] = x;
    location[1] = y;
    location[2] = z;
    for (int i = 0; i < 16; i++)
    {
        vertices[3 * i] *= w;
        vertices[3 * i + 1] *= b;
        vertices[3 * i + 2] *= h;
        vertices[3 * i] += x;
        vertices[3 * i + 1] += y;
        vertices[3 * i + 2] += z;
    }
    GLfloat largest = (w > b) ? ((w > h) ? w : h) : ((b > h) ? b : h);
    for (int i = 0; i < sizeof(texCoords) / sizeof(texCoords[0]); i++)
    {
        if (scaleTex)
            texCoords[i] = texCoords[i] * largest;
    }
    cubeVAO = new VAO;
    cubeVAO->Bind();
    cubeVBO = new VBO(vertices, sizeof(vertices));
    texVBO = new VBO(texCoords, sizeof(texCoords));
    normalVBO = new VBO(normal, sizeof(normal));
    cubeEBO = new EBO(indices, sizeof(indices));
}

void Cube::linkAttribs()
{
    cubeVAO->LinkAttrib(*cubeVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);
    cubeVAO->LinkAttrib(*texVBO, 1, 2, GL_FLOAT, 2 * sizeof(float), (void *)0);
    cubeVAO->LinkAttrib(*normalVBO, 2, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void *)0);
}
void Cube::Bind()
{
    cubeVAO->Bind();
    cubeVBO->Bind();
    cubeEBO->Bind();
}
void Cube::Unbind()
{
    cubeVAO->Unbind();
    cubeVBO->Unbind();
    texVBO->Unbind();
    normalVBO->Unbind();
    cubeEBO->Unbind();
}

void Cube::render()
{
    texture->Bind();
    cubeVAO->Bind();
    linkAttribs();
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
    cubeVAO->Unbind();
    texture->Unbind();
}
void Cube::sourceLink()
{
    cubeVAO->LinkAttrib(*cubeVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);
    
}
void Cube::sourceRender()
{
    cubeVAO->Bind();
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
    cubeVAO->Unbind();
}
void Cube::Delete()
{
    cubeVAO->Delete();
    cubeVBO->Delete();
    cubeEBO->Delete();
}
void Cube::linkTexture(Texture &texture)
{
    Cube::texture = &texture;
}

void Cube::translate(glm::vec3 cord)
{
    Cube cb(cord.x, cord.y, cord.z, this->width, this->breadth, this->height, false);
    for (int i = 0; i < 16; i++)
    {
        vertices[3 * i] = cb.vertices[3 * i];
        vertices[3 * i + 1] = cb.vertices[3 * i + 1];
        vertices[3 * i + 2] = cb.vertices[3 * i + 2];
    }
}