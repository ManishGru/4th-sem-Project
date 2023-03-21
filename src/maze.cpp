#ifndef __MAZE__
#define __MAZE__
#include <iostream>
#include <vector>
#include <ctime>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>

#include "cell.cpp"

#include "../inc/glad.h"
#include <GLFW/glfw3.h>

#include "../inc/glm/glm.hpp"
#include "../inc/glm/gtc/matrix_transform.hpp"
#include "../inc/glm/gtc/type_ptr.hpp"
#include "../inc/stb_image.h"
#include "../inc/shaderClass.h"
#include "../inc/VAO.h"
#include "../inc/VBO.h"
#include "../inc/EBO.h"
#include "../inc/Texture.h"
#include "../inc/Camera.h"
#include "../inc/cube.h"

#define WIDTH 1920
#define HEIGHT 1080

int last = 0;
int mx, my;
class Maze
{
public:
    int rows;                // Number of Rows in the maze
    int cols;                // Number of Columns in the maze
    int visited = 0;         // stores the number of cess visited
    std::vector<Cell> cells; // All the cells of the grid
    Cell *startcell;         // start cell in the maze
    Cell *endcell;           // end cell in the maze
    // initialize the maze

    Maze(Maze &&) = default;
    Maze(const Maze &) = default;
    Maze &operator=(Maze &&) = default;
    Maze &operator=(const Maze &) = default;

    Maze(int r = 16, int c = 16)
    {
        this->rows = r;
        this->cols = c;
        // define all the cells
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cells.push_back(*(new Cell(i, j)));
            }
        }
        startcell = &cells[0];
        startcell->isStart = true;
        endcell = &cells[getIndex(cols-1,rows-1)];
        endcell->isEnd = true;
    }
    // display all the cells
    void display(int x = -1, int y = -1)
    {
        // system("clear");
        for (auto &c : cells)
        {
            if (c.x == x && c.y == y)
                c.display(1);
            else
                c.display();
        }
        refresh();
    }
    // generate the maze
    void generateMaze()
    {
        Cell *current = &cells[0]; // selecting a 0th cell as initial cell in the maze
        current->visited = true;
        std::vector<Cell *> st; // stack to backtrack the path
        // loop to generate maze
        while (1)
        {
            std::vector<Cell *> neighbours; // stores the neighbour of current cell
            // top
            int index = getIndex(current->x, current->y - 1); // index of cell in the above of current cell
            if (index != -1)
            {
                Cell *top = &cells[index];
                if (!top->visited)
                {
                    neighbours.push_back(top); // stores the cell in the neighbour array;
                }
            }
            // right
            index = getIndex(current->x + 1, current->y);
            if (index != -1)
            {
                Cell *right = &cells[index];
                if (!right->visited)
                {
                    neighbours.push_back(right);
                }
            }
            // bottom
            index = getIndex(current->x, current->y + 1);
            if (index != -1)
            {
                Cell *bottom = &cells[index];
                if (!bottom->visited)
                {
                    neighbours.push_back(bottom);
                }
            }
            // left
            index = getIndex(current->x - 1, current->y);
            if (index != -1)
            {
                Cell *left = &cells[index];
                if (!left->visited)
                {
                    neighbours.push_back(left);
                }
            }
            // getmaxyx(stdscr, my, mx);
            // mvprintw(my - last - 1, 0, "x = %d y = %d ,%ld", current->x, current->y, neighbours.size());
            // last++;break;

            // if there is at least one neighbour in the array
            if (neighbours.size() != 0)
            {
                Cell *next = neighbours[std::rand() % neighbours.size()]; // chooses one of the neighbour randomly
                st.push_back(current);                                    // pushes the current cell into stack
                // check the location of the next cell and remove wall accordingly
                if (current->x < next->x)
                {
                    current->walls = current->walls ^ RIGHT; // removes the right wall of current cell
                    next->walls = next->walls ^ LEFT;        // removes the left wall of next cell
                }
                else if (current->x > next->x)
                {
                    current->walls = current->walls ^ LEFT;
                    next->walls = next->walls ^ RIGHT;
                }
                else if (current->y < next->y)
                {
                    current->walls = current->walls ^ BOTTOM;
                    next->walls = next->walls ^ TOP;
                }
                else if (current->y > next->y)
                {
                    current->walls = current->walls ^ TOP;
                    next->walls = next->walls ^ BOTTOM;
                }
                current = next;          // next is made the current
                current->visited = true; // make the current cell as visited
            }
            else if (st.size() > 0) // check if there is no neighbour and stack size is greater than 0
            {
                current = st[st.size() - 1];                         // get last cell as the current cell
                st.pop_back();                                       // remove the last cell
                float randomnum = (float)random() / (float)RAND_MAX; // get random number to remmove wall from the current cell
                if (randomnum > 0.85)                                // remove wall randomly 0.1 times
                {
                    std::vector<uint8_t> walls; // stores the walls of current cell
                    // check the wall and push it into the array
                    if (current->checkWall(TOP))
                    {
                        walls.push_back(TOP);
                    }
                    if (current->checkWall(RIGHT))
                    {
                        walls.push_back(RIGHT);
                    }
                    if (current->checkWall(BOTTOM))
                    {
                        walls.push_back(BOTTOM);
                    }
                    if (current->checkWall(LEFT))
                    {
                        walls.push_back(LEFT);
                    }
                    // if there are more than 1 walli
                    if (walls.size() > 1)
                    {
                        uint8_t wall = walls[random() % walls.size()]; // randomly choose the wall
                        // check if the wall selected is not border wall
                        if (
                            !(wall == TOP && current->y == 0) &&
                            !(wall == BOTTOM && current->y == rows - 1) &&
                            !(wall == RIGHT && current->x == cols - 1) &&
                            !(wall == LEFT && current->x == 0))
                        {
                            // remove selected wall
                            if (wall == TOP)
                            {
                                Cell *next = &cells[getIndex(current->x, current->y - 1)];
                                if (next->visited)
                                {
                                    current->walls = current->walls ^ TOP;
                                    next->walls = next->walls ^ BOTTOM;
                                }
                            }
                            else if (wall == RIGHT)
                            {
                                Cell *next = &cells[getIndex(current->x + 1, current->y)];
                                if (next->visited)
                                {
                                    current->walls = current->walls ^ RIGHT;
                                    next->walls = next->walls ^ LEFT;
                                }
                            }
                            else if (wall == BOTTOM)
                            {
                                Cell *next = &cells[getIndex(current->x, current->y + 1)];
                                if (next->visited)
                                {
                                    current->walls = current->walls ^ BOTTOM;
                                    next->walls = next->walls ^ TOP;
                                }
                            }
                            else if (wall == LEFT)
                            {
                                Cell *next = &cells[getIndex(current->x - 1, current->y)];
                                if (next->visited)
                                {
                                    current->walls = current->walls ^ LEFT;
                                    next->walls = next->walls ^ RIGHT;
                                }
                            }
                        }
                    }
                }
            }
            else // there is no neighbour and there is nothing in stack.
            {
                break;
            }
            // this->display(current->x, current->y);
            // usleep(100000);
        }
    }

    // get the index of the cell in the current grid using x and y of the cell
    // Returns -1 if the cell is out of bounds
    int getIndex(int x, int y)
    {
        if (x < 0 || y < 0 || x > cols - 1 || y > rows - 1)
        {
            return -1;
        }
        return x + y * cols;
    }

    void clear()
    {
        cells.clear();
        // std::vector<Cell>::iterator it;
        // for (auto it = cells.begin();  it != cells.end(); it++)
        // {
        //         cells.erase(it);
        // }
        int visited = 0;
        delete[] startcell;
        delete[] endcell;
    }
    void genMazeAgain()
    {
        this->clear();
        // define all the cells
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cells.push_back(*(new Cell(i, j)));
            }
        }
        startcell = &cells[0];
        startcell->isStart = true;
        endcell = &cells[cells.size() - 1];
        endcell->isEnd = true;
        this->generateMaze();
    }
    int display3d()
    {
        // GLFW initialization
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // widow creation
        GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Maze Solver", NULL, NULL);
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
        glViewport(0, 0, WIDTH, HEIGHT); // tell opengl the size of the view port

        Shader shaderProgram("./shaders/default.vert", "./shaders/default.frag"); // Compiles and links the vertex and fragment shaders

        Cube ground(-500.0f, -5.1f, -500.0f, 1000.0f, .1f, 1000.0f, 1);
        Cube start_indicator(startcell->x * 2 + 0.3, -5.0f, startcell->y * 2 + 0.3, 1.4f, 0.1f, 1.4f, 0);
        Cube end_indicator(endcell->x * 2 + 0.3, -5.0f, endcell->y * 2 + 0.3, 1.4f, 0.1f, 1.4f, 0);
        ground.linkAttribs();
        ground.Unbind();
        start_indicator.linkAttribs();
        start_indicator.Unbind();
        end_indicator.linkAttribs();
        end_indicator.Unbind();

        Texture wall("./resources/br", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
        wall.texUnit(shaderProgram, "tex0", 0);

        Texture starttex("./resources/start.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
        starttex.texUnit(shaderProgram, "tex0", 0);

        Texture endtex("./resources/end.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
        starttex.texUnit(shaderProgram, "tex0", 0);
        for (auto &cell : cells)
        {
            cell.init3d(wall);
        }
        // cells[0].init3d(wall);
        // create the texture in from the resoures tab
        Texture groundtex("./resources/grass.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
        groundtex.texUnit(shaderProgram, "tex0", 0);

        ground.linkTexture(groundtex);
        start_indicator.linkTexture(starttex);
        end_indicator.linkTexture(endtex);
        glEnable(GL_DEPTH_TEST);

        // for some maze viewing thingy
        //  Camera camera(WIDTH, HEIGHT, glm::vec3(-10.0f, 2.0f, -10.0f), 45.0f, 0.1f, 100.0f);
        //  camera.Rotate(180+45,glm::vec3(0.0f,1.0f,0.f));
        // for playing the maze game
        Camera camera(WIDTH, HEIGHT, glm::vec3((float)2 * (startcell->x) + 1.0f, -4.5f, (float)2 * (startcell->y) + 1.0f), 55.0f, 0.01f, 100.0f);
        if (!startcell->checkWall(RIGHT))
            camera.Rotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        else
            camera.Rotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

        // working loop and breaks if the window is closed
        while (!glfwWindowShouldClose(window))
        {
            int cameraCelli = floor(camera.Position.x / 2), cameraCellj = floor(camera.Position.z / 2);
            uint8_t camerawalls = cells[getIndex(cameraCelli, cameraCellj)].walls;
            // printf("%x\t",camerawalls);
            // std::cout << cameraCelli << "\t" << cameraCellj << std::endl;
            glClearColor(0.1f, 0.3f, 0.8f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            shaderProgram.Activate();
            camera.Matrix(shaderProgram, "camMatrix");
            ground.render();
            start_indicator.render();
            end_indicator.render();
            for (auto &cell : cells)
            {
                cell.display3d();
            }
            // cells[0].display3d();
            camera.Inputs(window, camerawalls);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        ground.Delete();
        wall.Delete();
        groundtex.Delete();
        start_indicator.Delete();
        end_indicator.Delete();

        for (auto &cell : cells)
        {
            cell.delete3d();
        }
        // cells[0].delete3d();
        shaderProgram.Delete();
        glfwDestroyWindow(window); // destroying the window in the end of the program
        glfwTerminate();
    }
};
#endif