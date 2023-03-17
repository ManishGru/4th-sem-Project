#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>
#include <ctime>

#include "./inc/glad.h"
#include <GLFW/glfw3.h>

// private includes
#include "./src/maze.cpp"
#include "./src/maze_dijkstra.cpp"
#include "./src/bot.cpp"
#include "./src/astar.cpp"

#include "inc/glm/glm.hpp"
#include "inc/glm/gtc/matrix_transform.hpp"
#include "inc/glm/gtc/type_ptr.hpp"
#include "inc/stb_image.h"
#include "inc/shaderClass.h"
#include "inc/VAO.h"
#include "inc/VBO.h"
#include "inc/EBO.h"
#include "inc/Texture.h"
#include "inc/Camera.h"

#define width 800
#define height 800
// #define Astric
#define _dijkstra
int rows = 13, cols = 41;


//vertices for pyramid
GLfloat vertices[] = {
    -0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44, 0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44, 5.0f, 0.0f,
    0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44, 0.0f, 0.0f,
    0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44, 5.0f, 0.0f,
    0.0f, 0.8f, 0.0f, 0.83f, 0.70f, 0.44, 2.5f, 5.0f};
//index of every vertix of the pyramid
GLuint indices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4};

int main()
{

    // GLFW initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::srand(std::time(nullptr));
    initscr();
    raw();
    Maze maze(rows, cols);

    system("clear");
    start_color();

    maze.generateMaze();
    maze.display();
    refresh();

#ifdef _dijkstra
    dijkstra dijkstra(rows, cols, maze);
    dijkstra.shortPath();
    refresh();

#endif

#ifdef Astric
    maze.display();
    refresh();
    aStar(maze, true);
    usleep(1400000);

    // system("clear");
    // start_color();

    // maze.genMazeAgain();
    // maze.generateMaze();

    refresh();
    // maze.display();
    aStar(maze, false);

#endif

    refresh();
    getch();
    endwin();
    GLFWwindow *window = glfwCreateWindow(width, height, "Maze Solver", NULL, NULL);
    if (window == NULL)
    {
        // creation failed
        std::cout << "Failed to create Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // tells glfw to make the window part of the current context
    // context: state of the opengl , OpenGL is a state machine
    gladLoadGL();                    // load needed configuration for openGL
    glViewport(0, 0, width, height); // tell opengl the size of the view port

    // window creation
    Shader shaderProgram("./shaders/default.vert", "./shaders/default.frag");//Compiles and links the vertex and fragment shaders

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    Texture saringan("./resources/br", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    saringan.texUnit(shaderProgram, "tex0", 0);

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
    // working loop and breaks if the window is closed
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.3f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();
        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1, 100.0f, shaderProgram, "camMatrix");
        saringan.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    saringan.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window); // destroying the window in the end of the program
    glfwTerminate();
    return 0;
}
