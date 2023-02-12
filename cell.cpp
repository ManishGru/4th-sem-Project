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

    Cell(int y, int x)
    {
        this->x = x;
        this->y = y;
        walls = TOP | LEFT |BOTTOM| RIGHT;
    }
    void display()
    {
        init_pair(1, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        if (checkWall(walls, TOP) || checkWall(walls, LEFT))
            mvprintw(y * 4, x * 5, "+");
        else
            mvprintw(y * 4, x * 5, " ");
        if (checkWall(walls, TOP))
            mvprintw(y * 4, x * 5 + 1, "---");
        else
            mvprintw(y * 4, x * 5 + 1, "   ");
        if (checkWall(walls, TOP) || checkWall(walls, RIGHT))
            mvprintw(y * 4, x * 5 + 4, "+");
        else
            mvprintw(y * 4, x * 5 + 4, " ");
        attroff(COLOR_PAIR(1));
        for (int i = 0; i < 2; i++)
        {
            attron(COLOR_PAIR(1));
            if (checkWall(walls, LEFT))
                mvprintw(y * 4 + 1 + i, x * 5, "|");
            else
                mvprintw(y * 4 + 1 + i, x * 5, " ");
            attroff(COLOR_PAIR(1));
            if (visited == true)
            {
                init_pair(5, COLOR_RED, COLOR_CYAN);
                attron(COLOR_PAIR(5));
                mvprintw(y * 4 + 1 + i, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(5));
            }
            else
            {
                attron(COLOR_PAIR(1));
                mvprintw(y * 4 + 1 + i, x * 5 + 1, "   ");
                attroff(COLOR_PAIR(1));
            }
            attron(COLOR_PAIR(1));
            if (checkWall(walls, RIGHT))
                mvprintw(y * 4 + 1 + i, x * 5 + 4, "|");
            else
                mvprintw(y * 4 + 1 + i, x * 5 + 4, " ");
            attroff(COLOR_PAIR(1));
        }
        attron(COLOR_PAIR(1));
        if (checkWall(walls, BOTTOM) || checkWall(walls, LEFT))
            mvprintw(y * 4 + 3, x * 5, "+");
        else
            mvprintw(y * 4 + 3, x * 5, " ");
        if (checkWall(walls, BOTTOM))
        {
            mvprintw(y * 4 + 3, x * 5 + 1, "---");
        }
        else
            mvprintw(y * 4 + 3, x * 5 + 1, "   ");
        if (checkWall(walls, BOTTOM) || checkWall(walls, RIGHT))
            mvprintw(y * 4 + 3, x * 5 + 4, "+");
        else
            mvprintw(y * 4 + 3, x * 5 + 4, " ");
        attroff(COLOR_PAIR(1));
    }
    bool checkWall(uint8_t walls, uint8_t side)
    {
        if ((walls & side) == 0)
        {
            return false;
        }
        return true;
    }
};

#endif