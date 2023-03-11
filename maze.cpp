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

    Maze(int rows = 16, int cols = 16)
    {
        this->rows = rows;
        this->cols = cols;
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
    }
    // display all the cells
    void display()
    {
        system("clear");
        for (auto &c : cells)
        {
            c.display();
        }
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
                if (randomnum > 0.9)                                 // remove wall randomly 0.1 times
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
                                current->walls = current->walls ^ TOP;
                                Cell *next = &cells[getIndex(current->x, current->y - 1)];
                                next->walls = next->walls ^ BOTTOM;
                            }
                            else if (wall == RIGHT)
                            {
                                current->walls = current->walls ^ RIGHT;
                                Cell *next = &cells[getIndex(current->x + 1, current->y)];
                                next->walls = next->walls ^ LEFT;
                            }
                            else if (wall == BOTTOM)
                            {
                                current->walls = current->walls ^ BOTTOM;
                                Cell *next = &cells[getIndex(current->x, current->y + 1)];
                                next->walls = next->walls ^ TOP;
                            }
                            else if (wall == LEFT)
                            {
                                current->walls = current->walls ^ LEFT;
                                Cell *next = &cells[getIndex(current->x - 1, current->y)];
                                next->walls = next->walls ^ RIGHT;
                            }
                        }
                    }
                }
            }
            else // there is no neighbour and there is nothing in stack.
            {
                break;
            }
            // this->display();
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
};
#endif