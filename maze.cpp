#ifndef __MAZE__
#define __MAZE__
#include <iostream>
#include <vector>
#include <random>
#include "./cell.cpp"

class Maze
{
public:
    int rows; // Number of Rows in the maze
    int cols; // Number of Columns in the maze
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
        for (auto &c : cells)
        {
            c.display();
        }
    }
    void generateMaze()
    {
        Cell current = cells[0];
        current.visited = true;
        std::vector<Cell> neighbours;
        // top
        int index = getIndex(current.x, current.y - 1);
        if (index != -1)
        {
            Cell top = cells[index];
            if (!top.visited)
            {
                neighbours.push_back(top);
            }
        }
        // right
        index = getIndex(current.x + 1, current.y);
        if (index != -1)
        {
            Cell right = cells[index];
            if (!right.visited)
            {
                neighbours.push_back(right);
            }
        }
        // bottom
        index = getIndex(current.x, current.y + 1);
        if (index != -1)
        {
            Cell bottom = cells[index];
            if (!bottom.visited)
            {
                neighbours.push_back(bottom);
            }
        }
        // left
        index = getIndex(current.x, current.y - 1);
        if (index != -1)
        {
            Cell left = cells[index];
            if (!left.visited)
            {
                neighbours.push_back(left);
            }
        }

        this->display();
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