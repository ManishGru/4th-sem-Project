#ifndef __CELL__
#define __CELL__
#include <iostream>
#include <ncurses.h>
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
    bool current = false;
    bool neighbours = false;
    bool dijsktrashortPath = false;
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
    void display()
    {
        init_pair(1, COLOR_BLACK, COLOR_GREEN);
        init_pair(2, COLOR_BLACK, COLOR_MAGENTA);
        init_pair(3, COLOR_BLACK, COLOR_CYAN);    // THIS IS THE PATH
        init_pair(4, COLOR_BLACK, COLOR_RED);     // CURRENT
        init_pair(5, COLOR_BLACK, COLOR_RED);     // NEIGHBOUR
        init_pair(6, COLOR_BLACK, COLOR_MAGENTA); // SHORTPATH

        if (checkWall(walls, TOP) || checkWall(walls, LEFT))
            mvprintw(y * 4, x * 5, "+");
        else
            mvprintw(y * 4, x * 5, " ");
        if (checkWall(walls, TOP))
            mvprintw(y * 4, x * 5 + 1, "---");
        else
        {
            if (dijsktrashortPath)
            {
                attron(COLOR_PAIR(6));
                mvprintw(y * 4, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(6));
            }
            else if (current)
            {
                attron(COLOR_PAIR(4));
                mvprintw(y * 4, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(4));
            }
            else if (neighbours)
            {
                attron(COLOR_PAIR(5));
                mvprintw(y * 4, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(5));
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
                if (dijsktrashortPath)
                {
                    attron(COLOR_PAIR(6));
                    mvprintw(y * 4 + 1 + i, x * 5 + 1, "   ");
                    attroff(COLOR_PAIR(6));
                }
                else if (current)
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(y * 4 + 1 + i, x * 5, " ");
                    attroff(COLOR_PAIR(4));
                }
                else if (neighbours)
                {
                    attron(COLOR_PAIR(5));
                    mvprintw(y * 4 + 1 + i, x * 5, " ");
                    attroff(COLOR_PAIR(5));
                }
                else
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(y * 4 + 1 + i, x * 5, " ");
                    attroff(COLOR_PAIR(3));
                }
            }
            if (dijsktrashortPath)
            {
                attron(COLOR_PAIR(6));
                mvprintw(y * 4 + 1 + i, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(6));
            }
            else if (current)
            {
                attron(COLOR_PAIR(4));
                mvprintw(y * 4 + 1 + i, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(4));
            }
            else if (neighbours)
            {
                attron(COLOR_PAIR(5));
                mvprintw(y * 4 + 1 + i, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(5));
            }
            else if (isStart)
            {
                attron(COLOR_PAIR(1));
                mvprintw(y * 4 + 1 + i, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(1));
            }
            else if (isEnd)
            {
                attron(COLOR_PAIR(6));
                mvprintw(y * 4 + 1 + i, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(6));
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
                if (dijsktrashortPath)
                {
                    attron(COLOR_PAIR(6));
                    mvprintw(y * 4 + 1 + i, x * 5 + 4, " ");
                    attroff(COLOR_PAIR(6));
                }
                else if (current)
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(y * 4 + 1 + i, x * 5 + 4, " ");
                    attroff(COLOR_PAIR(4));
                }
                else if (neighbours)
                {
                    attron(COLOR_PAIR(5));
                    mvprintw(y * 4 + 1 + i, x * 5 + 4, " ");
                    attroff(COLOR_PAIR(5));
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
            if (dijsktrashortPath)
            {
                attron(COLOR_PAIR(6));
                mvprintw(y * 4 + 3, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(6));
            }
            else if (current)
            {
                attron(COLOR_PAIR(5));
                mvprintw(y * 4 + 3, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(5));
            }
            else if (neighbours)
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
};

#endif