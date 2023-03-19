#ifndef __CELL__
#define __CELL__
#include <iostream>
#include <ncurses.h>
#include "../inc/cube.h"
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
    bool visited = false;
    bool isStart = false;
    bool isEnd = false;
    bool isOpen = false;
    bool isPath = false;
    std::vector<Cube> cubes;
    // bool neighbours = false;
    // bool dijsktrashortPath = false;
    // std::vector<Cell*> itsneighbours;
    // initialize the cell

    Cell() {}

    Cell(int y, int x)
    {
        this->x = x;
        this->y = y;
        walls = TOP | LEFT | BOTTOM | RIGHT;
    }
    // display the cell
    void display(int current = 0)
    {
        init_pair(1, COLOR_RED, COLOR_GREEN);
        init_pair(2, COLOR_RED, COLOR_RED);
        init_pair(3, COLOR_RED, COLOR_BLACK);
        init_pair(4, COLOR_RED, COLOR_BLUE); // NEIGHBOUR
        init_pair(5, COLOR_RED, COLOR_CYAN); // DIJKSTRA SHORTPATH

        if (checkWall(walls, TOP) || checkWall(walls, LEFT))
            mvprintw(y * 4, x * 5, "+");
        else
            mvprintw(y * 4, x * 5, " ");
        if (checkWall(walls, TOP))
            mvprintw(y * 4, x * 5 + 1, "---");
        else
        {
            if (isPath)
            {
                attron(COLOR_PAIR(5));
                mvprintw(y * 4, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(5));
            }
            else if (isOpen)
            {
                attron(COLOR_PAIR(4));
                mvprintw(y * 4, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(4));
            }
            else
            {
                attron(COLOR_PAIR(3));
                mvprintw(y * 4, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(3));
            }
        }
        if (checkWall(walls, TOP) || checkWall(walls, RIGHT))
            mvprintw(y * 4, x * 5 + 4, "+");
        else
            mvprintw(y * 4, x * 5 + 4, " ");
        for (int i = 0; i < 2; i++)
        {
            if (checkWall(walls, LEFT))
                mvprintw(y * 4 + 1 + i, x * 5, "|");
            else
            {

                if (isPath)
                {
                    attron(COLOR_PAIR(5));
                    mvprintw(y * 4 + 1 + i, x * 5, " ");
                    attroff(COLOR_PAIR(5));
                }
                else if (isOpen)
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(y * 4 + 1 + i, x * 5, " ");
                    attroff(COLOR_PAIR(4));
                }
                else
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(y * 4 + 1 + i, x * 5, " ");
                    attroff(COLOR_PAIR(3));
                }
            }
            if (current == 1)
            {
                attron(COLOR_PAIR(4));
                mvprintw(y * 4 + 1 + i, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(4));
            }
            else if (isStart)
            {
                attron(COLOR_PAIR(1));
                mvprintw(y * 4 + 1 + i, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(1));
            }
            else if (isEnd)
            {
                attron(COLOR_PAIR(2));
                mvprintw(y * 4 + 1 + i, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(2));
            }
            else if (isPath)
            {
                attron(COLOR_PAIR(5));
                mvprintw(y * 4 + 1 + i, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(5));
            }
            else if (isOpen)
            {
                attron(COLOR_PAIR(4));
                mvprintw(y * 4 + 1 + i, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(4));
            }

            else
            {
                attron(COLOR_PAIR(3));
                mvprintw(y * 4 + 1 + i, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(3));
            }
            if (checkWall(walls, RIGHT))
                mvprintw(y * 4 + 1 + i, x * 5 + 4, "|");
            else
            {

                if (isPath)
                {
                    attron(COLOR_PAIR(5));
                    mvprintw(y * 4 + 1 + i, x * 5 + 4, " ");
                    attroff(COLOR_PAIR(5));
                }
                else if (isOpen)
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(y * 4 + 1 + i, x * 5 + 4, " ");
                    attroff(COLOR_PAIR(4));
                }
                else
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(y * 4 + 1 + i, x * 5 + 4, " ");
                    attroff(COLOR_PAIR(3));
                }
            }
        }
        if (checkWall(walls, BOTTOM) || checkWall(walls, LEFT))
            mvprintw(y * 4 + 3, x * 5, "+");
        else
            mvprintw(y * 4 + 3, x * 5, " ");
        if (checkWall(walls, BOTTOM))
            mvprintw(y * 4 + 3, x * 5 + 1, "---");
        else
        {
            if (isPath)
            {
                attron(COLOR_PAIR(5));
                mvprintw(y * 4 + 3, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(5));
            }
            else if (isOpen)
            {
                attron(COLOR_PAIR(4));
                mvprintw(y * 4 + 3, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(4));
            }
            else
            {
                attron(COLOR_PAIR(3));
                mvprintw(y * 4 + 3, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(3));
            }
        }
        if (checkWall(walls, BOTTOM) || checkWall(walls, RIGHT))
            mvprintw(y * 4 + 3, x * 5 + 4, "+");
        else
            mvprintw(y * 4 + 3, x * 5 + 4, " ");
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
    void init3d(Texture &texture)
    {
        cubes.push_back(Cube(2 * x + 0.0f, -5.0f, 2 * y + 0.0f, 0.3f, 1.0f, 0.3f));
        if (checkWall(TOP))
            cubes.push_back(Cube(2 * x + 0.3f, -5.0f, 2 * y + 0.0f, 1.4f, 1.0f, 0.3f)); // top wall
        cubes.push_back(Cube(2 * x + 1.7f, -5.0f, 2 * y + 0.0f, 0.3f, 1.0f, 0.3f));
        if (checkWall(LEFT))
            cubes.push_back(Cube(2 * x + 0.0f, -5.0f, 2 * y + 0.3f, 0.3f, 1.0f, 1.4f)); // left wall
        cubes.push_back(Cube(2 * x + 0.0f, -5.0f, 2 * y + 1.7f, 0.3f, 1.0f, 0.3f));
        if (checkWall(BOTTOM))
            cubes.push_back(Cube(2 * x + 0.3f, -5.0f, 2 * y + 1.7f, 1.4f, 1.0f, 0.3f)); // bottom wall
        cubes.push_back(Cube(2 * x + 1.7f, -5.0f, 2 * y + 1.7f, 0.3f, 1.0f, 0.3f));
        if (checkWall(RIGHT))
            cubes.push_back(Cube(2 * x + 1.7f, -5.0f, 2 * y + 0.3f, 0.3f, 1.0f, 1.4f)); // right wall
        for (auto &cuboid : cubes)
        {
            cuboid.linkAttribs();
            cuboid.Unbind();
            cuboid.linkTexture(texture);
        }
    }
    void display3d()
    {
        for (auto &cuboid : cubes)
            cuboid.render();
    }
    void delete3d()
    {
        for (auto &cuboid : cubes)
            cuboid.Delete();
    }
};

#endif