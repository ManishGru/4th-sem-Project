
#include <iostream>
#include "./maze.cpp"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <bits/stdc++.h>
#include "./cell.cpp"

using namespace std;

class floodfill
{

public:
    // int x, y;
    // Maze *maze;
    Cell *current;

    void initializeFloodfillValue(Maze *maze);
    void floodfillShortestPath(Maze *maze);
    void Floodfill(Maze*);
    Cell *get_smallest_neighbouring_value(Cell *);
};
Cell *floodfill::get_smallest_neighbouring_value(Cell *current)
{
}
void floodfill::initializeFloodfillValue(Maze *maze)
{
    // maze->endcell->value = 0;

    // for (int val = 0; val < maze->rows + maze->cols - 1; val++)
    // {
    for (int i = 0; i < maze->rows; i++)
    {
        for (int j = 0; j < maze->cols; j++)
        {
            // if (maze->cells[maze->getIndex(i, j)].value = val - 1)
            // {
            //     if (i > 0 && maze->cells[maze->getIndex(i - 1, j)].value > val)
            //     {
            //         maze->cells[maze->getIndex(i - 1, j)].value = val;
            //     }

            //     if (i < maze->rows - 1 && maze->cells[maze->getIndex(i + 1, j)].value > val)
            //     {
            //         maze->cells[maze->getIndex(i + 1, j)].value = val;
            //     }
            //     if (j > 0 && maze->cells[maze->getIndex(i, j - 1)].value > val)
            //     {
            //         maze->cells[maze->getIndex(i, j - 1)].value = val;
            //     }
            //     if (i < maze->cols - 1 && maze->cells[maze->getIndex(i, j + 1)].value > val)
            //     {
            //         maze->cells[maze->getIndex(i, j + 1)].value = val;
            //     }
            //     std::cout << i << " " << j << " " << maze->cells[maze->getIndex(i, j)].value << std::endl;
            // }

            maze->cells[maze->getIndex(i, j)].value = (maze->rows + maze->cols) - (i + j) - 2;

            std::cout << "\t" << maze->cells[maze->getIndex(i, j)].value;
        }
        std::cout << std::endl;
    }
    // }
}

void floodfill::floodfillShortestPath(Maze *maze)
{

    //     void push_all_the_neighbouring_cell_in_stack(vector<Cell *> vect)
    //     {
    //         for (auto it : vect->value)
    //         {
    //             s.push(it);
    //         }
}
//     s.push(current_cell->value);
void floodfill::Floodfill(Maze *maze)
{
    Cell *current;
    stack<Cell *> s;
    Cell *md;

    while (!s.empty())
    {
        current = s.top();
        s.pop();

        std::vector<Cell *> open_neighbours;
        std::vector<Cell *> neighbours_cell_of_current_cell;

        if (!current->checkWall(TOP))
        {
            int index = maze->getIndex(current->x, current->y - 1); // index of cell in the above of current cell
            if (index != -1)
            {
                Cell *top = &maze->cells[index];
                open_neighbours.push_back(top); // stores the cell in the neighbour array;
            }
        }
        if (!current->checkWall(BOTTOM))
        {
            int index = maze->getIndex(current->x, current->y + 1); // index of cell in the above of current cell
            if (index != -1)
            {
                Cell *bottom = &maze->cells[index];
                open_neighbours.push_back(bottom); // stores the cell in the neighbour array;
            }
        }
        if (!current->checkWall(LEFT))
        {
            int index = maze->getIndex(current->x - 1, current->y); // index of cell in the above of current cell
            if (index != -1)
            {
                Cell *left = &maze->cells[index];
                open_neighbours.push_back(left); // stores the cell in the neighbour array;
            }
        }
        if (!current->checkWall(RIGHT))
        {
            int index = maze->getIndex(current->x + 1, current->y); // index of cell in the above of current cell
            if (index != -1)
            {
                Cell *right = &maze->cells[index];
                open_neighbours.push_back(right); // stores the cell in the neighbour array;
            }
        }
        //     // now storing all the neighbouring cell of the current cell
        int index = maze->getIndex(current->x, current->y - 1); // index of cell in the above of current cell
        if (index != -1)
        {
            Cell *top = &maze->cells[index];
            neighbours_cell_of_current_cell.push_back(top); // stores the cell in the neighbour array;
        }
        index = maze->getIndex(current->x, current->y + 1); // index of cell in the above of current cell
        if (index != -1)
        {
            Cell *bottom = &maze->cells[index];
            neighbours_cell_of_current_cell.push_back(bottom); // stores the cell in the neighbour array;
        }
        index = maze->getIndex(current->x - 1, current->y); // index of cell in the above of current cell
        if (index != -1)
        {
            Cell *left = &maze->cells[index];
            neighbours_cell_of_current_cell.push_back(left); // stores the cell in the neighbour array;
        }
        index = maze->getIndex(current->x + 1, current->y); // index of cell in the above of current cell
        if (index != -1)
        {
            Cell *right = &maze->cells[index];
            neighbours_cell_of_current_cell.push_back(right); // stores the cell in the neighbour array;
        }


        
        md = get_smallest_neighbouring_value(current);

        if (md->value != current->value - 1)
        {
            current->value = md->value + 1;
            s.push(current);
            for (auto it : neighbours_cell_of_current_cell)
            {
                s.push(it);
            }
            //                 push_all_the_neighbouring_cell_in_stack(vector<Cell *> neighbours_cell_of_current_cell);
            //                 Floodfill(s.pop())
            //             }
            //             else
            //             {
            //                 s.pop();
            //             }
            //         }
        }
    }
}
