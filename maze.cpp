#ifndef __MAZE__
#define __MAZE__
#include <iostream>
#include <vector>
#include <ctime>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#include "./cell.cpp"

int last = 0;
int mx, my;

class Maze
{
public:
    int rows;        // Number of Rows in the maze
    int cols;        // Number of Columns in the maze
    int visited = 0; // stores the number of cess visited
    std::vector<Cell> cells;

    Maze(int rows = 16, int cols = 16)
    {
        this->rows = rows;
        this->cols = cols;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cells.push_back(*(new Cell(i, j)));
            }
        }
    }
    void display()
    {
        system("clear");
        for (auto &c : cells)
        {
            c.display();
        }
    }
    void generateMaze()
    {
        Cell *current = &cells[0];
        current->visited = true;
        std::vector<Cell *> st;
        while (visited < cells.size())
        {
            std::vector<Cell *> neighbours;
            // top
            int index = getIndex(current->x, current->y - 1);
            if (index != -1)
            {
                Cell *top = &cells[index];
                if (!top->visited)
                {
                    neighbours.push_back(top);
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
            if (neighbours.size() != 0)
            {
                Cell *next = neighbours[std::rand() % neighbours.size()];
                st.push_back(current);
                if (current->x < next->x)
                {
                    current->walls = current->walls ^ RIGHT;
                    next->walls = next->walls ^ LEFT;
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
                current = next;
                current->visited = true;
            }
            else if (st.size() > 0)
            {
                current = st[st.size()-1];
                st.pop_back();
            }
            else
            {
                break;
            }
            this->display();
        }
    }
    int getIndex(int x, int y)
    {
        if (x < 0 || y < 0 || x > cols - 1 || y > rows - 1)
        {
            return -1;
        }
        return x + y * cols;
    }
};
#endif