#include "../inc/cube.h"
Cube::Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat b, GLfloat h)
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
    cubeVAO = new VAO;
    cubeVAO->Bind();
    cubeVBO = new VBO(vertices, sizeof(vertices));
    texVBO = new VBO(texCoords, sizeof(texCoords));
    cubeEBO = new EBO(indices, sizeof(indices));
}

void Cube::linkAttribs()
{
    cubeVAO->LinkAttrib(*cubeVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);
    cubeVAO->LinkAttrib(*texVBO, 1, 2, GL_FLOAT, 2 * sizeof(float), (void *)0);
}
void Cube::Unbind()
{
    cubeVAO->Unbind();
    cubeVBO->Unbind();
    cubeEBO->Unbind();
}

void Cube::render(GLFWwindow &window, Shader &shader, Camera &camera)
{
    // shader.Activate();
    // camera.Matrix(shader, "camMatrix");
    texture->Bind();
    cubeVAO->Bind();
    linkAttribs();
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
    cubeVAO->Unbind();
    texture->Unbind();
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