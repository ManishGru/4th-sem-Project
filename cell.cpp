#ifndef __CELL__
#define __CELL__
#include <iostream>
#include <ncurses.h>
#include "./maze.cpp"
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
    //initialize the cell
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
        init_pair(2, COLOR_BLACK, COLOR_RED);
        init_pair(3, COLOR_BLACK, COLOR_WHITE);
        if (checkWall(walls, TOP) || checkWall(walls, LEFT))
            mvprintw(y * 4, x * 5, "+");
        else
            mvprintw(y * 4, x * 5, " ");
        if (checkWall(walls, TOP))
            mvprintw(y * 4, x * 5 + 1, "---");
        else
        {
            attron(COLOR_PAIR(3));
            mvprintw(y * 4, x * 5 + 1, "   ");
            attroff(COLOR_PAIR(3));
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
                attron(COLOR_PAIR(3));
                mvprintw(y * 4 + 1 + i, x * 5, " ");
                attroff(COLOR_PAIR(3));
            }
            if (isStart)
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
                attron(COLOR_PAIR(3));
                mvprintw(y * 4 + 1 + i, x * 5 + 4, " ");
                attroff(COLOR_PAIR(3));
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
            attron(COLOR_PAIR(3));
            mvprintw(y * 4 + 3, x * 5 + 1, "   ");
            attroff(COLOR_PAIR(3));
        }
        if (checkWall(walls, BOTTOM) || checkWall(walls, RIGHT))
            mvprintw(y * 4 + 3, x * 5 + 4, "+");
        else
            mvprintw(y * 4 + 3, x * 5 + 4, " ");
    }
    //check side in the given wall
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
};

#endif
