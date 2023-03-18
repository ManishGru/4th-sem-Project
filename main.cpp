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
#include "inc/cube.h"

#define width 800
#define height 800
// #define Astric
#define _dijkstra
int rows = 13, cols = 41;

// vertices for pyramid
GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // 0
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // 1
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   // 2
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // 3
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  // 4
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   // 5
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    // 6
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f,   // 7
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 0
    -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,  // 1
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f,   // 2
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // 3
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f,  // 4
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   // 5
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    // 6
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f,   // 7
};
// index of every vertix of the pyramid
GLuint indices[] = {
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
    // getch();
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
    Shader shaderProgram("./shaders/default.vert", "./shaders/default.frag"); // Compiles and links the vertex and fragment shaders
    Cube cube(-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f);
    Cube cube1(0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f);
    Cube cube2(0.5f, -0.5f, -0.0f, 0.3f, 0.2f, 0.4f);
    Cube cube3(0.0f, 1.0f, 0.0f, 0.5f, 0.7f, 0.5f);


    cube.linkAttribs();
    cube1.linkAttribs();
    cube2.linkAttribs();
    cube3.linkAttribs();


    cube.Unbind();
    cube1.Unbind();
    cube2.Unbind();
    cube3.Unbind();

    Texture wall("./resources/br", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    wall.texUnit(shaderProgram, "tex0", 0);
    cube.linkTexture(wall);
    cube1.linkTexture(wall);
    cube2.linkTexture(wall);
    cube3.linkTexture(wall);
    glEnable(GL_DEPTH_TEST);
    Camera camera(width, height, glm::vec3(2.0f, 2.0f, 2.0f), 45.0f, 0.1f, 100.0f);
    // working loop and breaks if the window is closed
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.3f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();
        camera.Matrix(shaderProgram, "camMatrix");
        cube.render(*window, shaderProgram, camera);
        cube1.render(*window, shaderProgram, camera);
        cube2.render(*window, shaderProgram, camera);
        cube3.render(*window, shaderProgram, camera);
        camera.Inputs(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    cube.Delete();
    cube1.Delete();
    cube2.Delete();
    cube3.Delete();
    wall.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window); // destroying the window in the end of the program
    glfwTerminate();
    return 0;
}
