#include <iostream>
#include <stdlib.h>
#include "commonShader.hpp"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "KeyMouse.h"
#include "./maze.cpp"
#include "cell.h"
using namespace glm;

float width = 1024;
float height = 768;

vec3 lightPos = vec3(4.0f / 5, 3.0f / 5, 3.0f / 5);
GLfloat g_color_buffer_data[8 * 3];

GLfloat l = 0.5f, b = 0.1f, h = 0.3f;
GLfloat Ex = l / 2, Wai = h / 2, Jed = b / 2;
GLfloat vertices[] = {
    Ex, Wai, Jed,
    Ex, Wai, -Jed,
    Ex, -Wai, Jed,
    Ex, -Wai, -Jed,
    -Ex, Wai, Jed,
    -Ex, Wai, -Jed,
    -Ex, -Wai, Jed,
    -Ex, -Wai, -Jed};

GLuint vertexElement[] = {
    0, 1, 3,
    0, 3, 2,
    0, 2, 6,
    0, 6, 4,
    0, 1, 5,
    0, 5, 4,
    1, 3, 7,
    1, 7, 5,
    2, 3, 7,
    2, 7, 6,
    4, 5, 7,
    4, 7, 6};

GLfloat g_normal_data[] = {
    Ex, Wai, Jed,
    Ex, Wai, -Jed,
    Ex, -Wai, Jed,
    Ex, -Wai, -Jed,
    -Ex, Wai, Jed,
    -Ex, Wai, -Jed,
    -Ex, -Wai, Jed,
    -Ex, -Wai, -Jed};

const char *vertexShaderSource = "./shader.vert";
const char *fragmentShaderSource = "./shader.frag";
GLFWwindow *CreateWindow();

void display_4x4(std::string tag, glm::mat4 m4)
{
    std::cout << tag << '\n';
    for (int col = 0; col < 4; ++col)
    {
        std::cout << "| ";
        for (int row = 0; row < 4; ++row)
        {
            std::cout << m4[row][col] << '\t';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int main()
{
    GLFWwindow *window = CreateWindow();
    /*-------------------------------*/
    Control KeyMouse(window);

    mat4 Projection = perspective(radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    mat4 View = lookAt(vec3(3, 5, 3),
                       vec3(4.0f, 0, 4.0f),
                       vec3(0, 1, 0));
    mat4 Model = mat4(1.0f);
    mat4 mvp = Projection * View * Model;

    /*-------------------------------*/

    GLuint shaderProgram = LoadShaders(vertexShaderSource, fragmentShaderSource);

    GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
    GLuint lightp = glGetUniformLocation(shaderProgram, "lightPos");
    for (int i = 0; i < 8 * 3; i++)
    {
        srand(i);
        g_color_buffer_data[i] = 0.2f; // float(rand()) / static_cast<float>(RAND_MAX);
    }
    /*-------------------------------*/

    VAO vertexArr;
    vertexArr.Bind();
    VBO colorBuff(g_color_buffer_data, sizeof(g_color_buffer_data));
    VBO vBuf(vertices, sizeof(vertices));
    VBO normalBuff(g_normal_data, sizeof(g_normal_data));
    EBO vIndices(vertexElement, sizeof(vertexElement));

    vertexArr.LinkAttrib(vBuf, 0, 3, GL_FLOAT, 36 * sizeof(float), (void *)0);
    vertexArr.LinkAttrib(colorBuff, 1, 3, GL_FLOAT, 36 * sizeof(float), (void *)0);
    vertexArr.LinkAttrib(normalBuff, 2, 3, GL_FLOAT, 36 * sizeof(float), (void *)0);

    vertexArr.UnBind();
    vBuf.UnBind();
    normalBuff.UnBind();
    colorBuff.UnBind();
    vIndices.UnBind();

    /*----------------------------------*/
    int rows = 20, cols = 20;
    Maze maze(rows, cols);
    maze.generateMaze();

    /*----------------------------------*/

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
    glUniform3fv(lightp, 1, &lightPos[0]);

    float angle = -90.0f;

    do
    {
        glClearColor(0.5f, 0.5f, 0.5f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        vertexArr.Bind();

        // Ex = l / 2, Wai = h / 2, Jed = b / 2;
        // vertexArr.LinkAttrib(vBuf, 0, 3, GL_FLOAT, 36 * sizeof(float), (void *)0);

        for (int i = 0; i < rows * cols; i++)
        {
            for (int j = 0; j < maze.cells[i].model.size(); j++)
            {
                glUseProgram(shaderProgram);

                glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

                Projection = KeyMouse.getProjectionMatrix();
                KeyMouse.computeMatrices();
                View = KeyMouse.getViewMatrix();

                mvp = Projection * View * maze.cells[i].model[j];

                glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);
            }
        }
        // vertexArr.UnBind();
        // vertexArr.Bind();

        // Ex = 4.0f, Wai = 4.0f, Jed = 2.0f;
        // vBuf = VBO(vertices, sizeof(vertices));
        // vertexArr.LinkAttrib(vBuf, 0, 3, GL_FLOAT, 36 * sizeof(float), (void *)0);
        // vBuf.UnBind();
        // glUseProgram(shaderProgram);
        // glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
        // Model = mat4(1.0f);
        // Model = translate(Model, vec3(-1.0f, 0.3f, 0.3f));
        // mvp = Projection * View * Model;

        // glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);
    vertexArr.Delete();
    colorBuff.Delete();
    vBuf.Delete();
    vIndices.Delete();
    normalBuff.Delete();
    glDeleteProgram(shaderProgram);
}

GLFWwindow *CreateWindow()
{
    if (!glfwInit())
    {
        fprintf(stderr, "failed to init\n");
        // return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window;
    window = glfwCreateWindow(width, height, "Dumb Learner", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "failed to open\n");
        glfwTerminate();
        // return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, 1000, 800);

    return window;
}