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

#define width 1440
#define height 900
// #define Astric
#define _dijkstra
int rows = 13, cols = 41;

int main()
{

    // GLFW initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // window creation

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

    //working loop and breaks if the window is closed
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.3f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    endwin();
    return 0;
}
