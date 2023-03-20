
#include <iostream>
#include "./maze.cpp"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <stack>
#include<bits/stdc++.h>
#include "./cell.cpp"

using namespace std;


/*int node ::get_smallest_neighbouring_value(node this_node)
{
    int smallest_neighbour_value=1;
    if (this_node->left->value!=NULL)&&(this_node->left->right!=NULL)&&(this_node->left->value<smallest_neighbour_value)
    {
        smallest_neighbour_value=this_node->left->value;
    }
    else if(this_node->right->value)&&(this_node->right->left!=NULL)&&(this_node->right->value<smallest_neighbour_value)
    {
        smallest_neighbour_value-this_node->right->value;
    }
    else if(this_node->top->value)&&(this_node->top->bottom!=NULL)&&(this_node->top->value<smallest_neighbour_value)
    {
        smallest_neighbour_value-this_node->top->value;
    }else if(this_node->bottom->value)&&(this_node->bottom->top!=NULL)&&(this_node->bottom->value<smallest_neighbour_value)
    {
        smallest_neighbour_value-this_node->bottom->value;
    }

    return smallest_neighbour_value;


}*/
class floodfill{

    public:
        int x,y;
        Maze *maze;
        Cell *current;

        void initializeFloodfillValue(Maze *maze);
        void floodfillShortestPath(Maze *maze,Cell *current );
}

void floodfill::initializeFloodfillValue(Maze *maze)
{       Cell *cell; 
    maze->startcell->value=0;

    for(int val=1;val<maze->rows*maze->cols;val++)
    {
        for(int i=0;i<maze->rows;i++)
        {
            for(int j=0;j<maze->cols;j++)
            {
                if(maze->cells[maze->getIndex(cell->x=i,cell->y=j)].value=val-1)
                {   
                    if(i>0 && maze->cells[maze->getIndex(cell->x=i-1 , cell->y=j)].value>val)
                    {
                        maze->cells[maze->getIndex(cell->x=i-1 , cell->y=j)].value=val;
                    }

                    if(i<maze->rows-1&& maze->cells[maze->getIndex(cell->x=i+1 , cell->y=j)].value>val)
                    {
                        maze->cells[maze->getIndex(cell->x=i+1 , cell->y=j)].value=val;
                    }
                    if(j>0 && maze->cells[maze->getIndex(cell->x=i , cell->y=j-1)].value>val)
                    {
                        maze->cells[maze->getIndex(cell->x=i , cell->y=j-1)].value=val;
                    }
                    if(i<maze->cols-1&& maze->cells[maze->getIndex(cell->x=i , cell->y=j+1)].value>val)
                    {
                        maze->cells[maze->getIndex(cell->x=i , cell->y=j+1)].value=val;
                    }


                    
                }
            }
        }
    }


    
}


void floodfill::floodfillShortestPath(Maze *maze ,Cell *current)
{   stack<int>s;
    std::vector<Cell*>open_neighbours;
    std::vector<Cell*>neighbours_cell_of_current_cell;

    if(!current->checkWall(TOP))
    {
        int index = maze->getIndex(current->x, current->y - 1); // index of cell in the above of current cell
            if (index != -1)
            {
                Cell *top = &maze->cells[index];
                if (!top->visited)
                {
                    open_neighbours.push_back(top); // stores the cell in the neighbour array;
                }
            }
    }
    if(!current->checkWall(BOTTOM))
    {
        int index = maze->getIndex(current->x, current->y + 1); // index of cell in the above of current cell
            if (index != -1)
            {
                Cell *bottom = &maze->cells[index];
                if (!bottom->visited)
                {
                    open_neighbours.push_back(bottom); // stores the cell in the neighbour array;
                }
            }
    }
    if(!current->checkWall(LEFT))
    {
        int index = maze->getIndex(current->x-1, current->y); // index of cell in the above of current cell
            if (index != -1)
            {
                Cell *left = &maze->cells[index];
                if (!left->visited)
                {
                    open_neighbours.push_back(left); // stores the cell in the neighbour array;
                }
            }
    }
    if(!current->checkWall(RIGHT))
    {
        int index = maze->getIndex(current->x+1, current->y); // index of cell in the above of current cell
            if (index != -1)
            {
                Cell *right = &maze->cells[index];
                if (!right->visited)
                {
                    open_neighbours.push_back(right); // stores the cell in the neighbour array;
                }
            }
    }
    //now storing all the neighbouring cell of the current cell
    int index = maze->getIndex(current->x, current->y - 1); // index of cell in the above of current cell
            if (index != -1)
            {
                Cell *top = &maze->cells[index];
                if (!top->visited)
                {
                    neighbours_cell_of_current_cell.push_back(top); // stores the cell in the neighbour array;
                }
            }
    int index = maze->getIndex(current->x, current->y + 1); // index of cell in the above of current cell
            if (index != -1)
            {
                Cell *bottom = &maze->cells[index];
                if (!bottom->visited)
                {
                    neighbours_cell_of_current_cell.push_back(bottom); // stores the cell in the neighbour array;
                }
            }
    int index = maze->getIndex(current->x-1, current->y ); // index of cell in the above of current cell
            if (index != -1)
            {
                Cell *left = &maze->cells[index];
                if (!left->visited)
                {
                    neighbours_cell_of_current_cell.push_back(left); // stores the cell in the neighbour array;
                }
            }
    int index = maze->getIndex(current->x+1, current->y ); // index of cell in the above of current cell
            if (index != -1)
            {
                Cell *right = &maze->cells[index];
                if (!right->visited)
                {
                    neighbours_cell_of_current_cell.push_back(right); // stores the cell in the neighbour array;
                }
            }


    int md;
    
    void push_all_the_neighbouring_cell_in_stack(vector<Cell*>vect)
    {
        for(auto it:vect->value)
        {
            s.push(it);
        }
    }
    s.push(current_cell->value);
    void Floodfill(int curr_cell_loc)
    {

    
        while(!s.empty())
        {
            static curr_Cell_loc=s.pull();
            static md=get_smallest_neighbouring_value(this_node);
        
            if(md!=curr_Cell_loc-1)
            {
                current_cell->value=md+1;
                //s.push(current_cell->value);
                push_all_the_neighbouring_cell_in_stack(vector<Cell*>neighbours_cell_of_current_cell);
                Floodfill(s.pop())
            




            }
            else{
                s.pop();
                }

        }
    
    }


}










