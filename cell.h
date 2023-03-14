#ifndef __CELL__
#define __CELL__
#include <iostream>
#include "glad/glad.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

// #include "./maze.cpp"
#define TOP 0X01
#define LEFT 0X02
#define BOTTOM 0X04
#define RIGHT 0X08

class Cell
{
public:
    int x;
    int y;
    uint8_t walls;
    std::vector<glm::mat4> model;
    bool visited = false;
    bool isStart = false;
    bool isEnd = false;
    bool isOpen = false;
    bool isPath = false;

    Cell() {}

    Cell(int y, int x)
    {
        this->x = x;
        this->y = y;
        walls = TOP | LEFT | BOTTOM | RIGHT;
    }
    // display the cell
    void display()
    {
        model.clear();
        GLfloat l = 0.5f, b = 0.1, h = 0.01;

        if (checkWall(walls, TOP))
            model.push_back(translate(mat4(1.0f), vec3(x * (l - b), 0.0f, y * (l - b)))); // TOP

        if (checkWall(walls, LEFT))
            model.push_back(rotate(translate(mat4(1.0f), vec3(x * (l - b) - (l / 2 - b / 2), 0.0f, l / 2 + y * (l - b))), radians(90.0f), vec3(0.0f, l, 0.0f))); // LEFT

        if (checkWall(walls, BOTTOM))
            model.push_back(translate(mat4(1.0f), vec3(x * (l - b), 0.0f, l + y * (l - b)))); // BOTTOM

        if (checkWall(walls, RIGHT))
            model.push_back(rotate(translate(mat4(1.0f), vec3(l + x * (l - b) - (l / 2 + b / 2), 0.0f, l / 2 + y * (l - b))), radians(90.0f), vec3(0.0f, l, 0.0f))); // RIGHT
    }

    // check side in the given wall
    bool checkWall(uint8_t walls, uint8_t side)
    {
        if ((walls & side) == 0)
        {
            return false;
        }
        return true;
    }
    // check side of the current cell
    bool checkWall(uint8_t side)
    {
        if ((this->walls & side) == 0)
        {
            return false;
        }
        return true;
    }

    bool operator==(const Cell &rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
};

#endif
