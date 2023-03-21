#include <queue>
#include <iostream>
#include <unistd.h>
#include <math.h>


#include "maze.cpp"
#include "cell.cpp"
using namespace std;

int Rows, Cols;
/*---------------------------------------*/
/*
    Star Class contain each cell and its f,g,h scores, neighbours and their parents
*/
class Star
{
public:
    Cell *cell;
    long g_score;
    long h_score;
    long f_score;
    std::vector<Star> itsneighbours;
    Star *previous;

    Star()
    {
        g_score = INT16_MAX;
        h_score = INT16_MAX;
        f_score = INT16_MAX;
        previous = NULL;
    }
    Star(Cell *c)
    {
        cell = c;
        g_score = INT16_MAX;
        h_score = INT16_MAX;
        f_score = INT16_MAX;
        previous = NULL;
    }
    Star(Cell *c, int g, int h, int f)
    {
        cell = c;
        g_score = g;
        h_score = h;
        f_score = f;
        previous = NULL;
    }

    Star(Star &&) = default;
    Star(const Star &) = default;
    Star &operator=(Star &&) = default;
    Star &operator=(const Star &) = default;

    inline bool operator==(Star s) // checks if two cells are same comparing their indices
    {
        if ((s.cell->x == cell->x) && (s.cell->y == cell->y))
            return 1;
        else
            return 0;
    }

    inline int getIndex() // convert (x,y) into index
    {
        if (cell->x < 0 || cell->y < 0 || this->cell->x > Rows - 1 || cell->y > Cols - 1)
        {
            return -1;
        }
        return cell->x + cell->y * Cols;
    }
};
/*---------------------------------------*/
inline int getIndex(int x, int y)
{
    if (x < 0 || y < 0 || x > Cols - 1 || y > Rows - 1)
    {
        return -1;
    }
    return x + y * Cols;
}

inline int h(Cell c1, Cell c2) // heuristics
{
    return (sqrt((c2.x - c1.x) * (c2.x - c1.x) + (c2.y - c1.y) * (c2.y - c1.y)));
}
/*---------------------------------------*/
void aStar(Maze &maze, int check) // main function that compute shortest path
{
    Rows = maze.rows, Cols = maze.cols;
    // int s = maze.getIndex(maze.startcell->x, maze.startcell->y);
    // int e = maze.getIndex(maze.endcell->x, maze.endcell->y);
    Star end(maze.endcell, INT16_MAX, INT16_MAX, INT16_MAX);
    Star start(maze.startcell, 0, 0, 0);

    vector<Star> openSet;   // contain those cells which are next to be visited
    vector<Star> closedSet; // contain those cells which are already visited

    openSet.push_back(start); // initilize

    int count = 0;
    while (1) // loop
    {
        int winner = 0;
        if (openSet.size() == 0) // chech if any cell is left to be visited before finding end cell
        {
            printw("nosolution!!!");
            return;
        }
        for (int i = 0; i < openSet.size(); i++) // make the decision which cell to choose next
        {
            if (check) // choose according to g_score
            {
                if (openSet[i].g_score < openSet[winner].g_score)
                {
                    winner = i;
                }
            }
            else // choose according to g_score
            {
                if (openSet[i].f_score < openSet[winner].f_score)
                {
                    winner = i;
                }
            }
        }

        Star current = openSet[winner];

        /*
            find the neighbouring cells to the current cell
        */
        int x;

        if (!(current.cell->checkWall(TOP)))
        {
            x = getIndex(current.cell->x, current.cell->y - 1);
            if (x != -1)
                current.itsneighbours.push_back(Star(&maze.cells[x], INT16_MAX, INT16_MAX, INT16_MAX));
        }
        if (!(current.cell->checkWall(BOTTOM)))
        {
            x = getIndex(current.cell->x, current.cell->y + 1);
            if (x != -1)
                current.itsneighbours.push_back(Star(&maze.cells[x], INT16_MAX, INT16_MAX, INT16_MAX));
        }
        if (!current.cell->checkWall(LEFT))
        {
            x = getIndex(current.cell->x - 1, current.cell->y);
            if (x != -1)
                current.itsneighbours.push_back(Star(&maze.cells[x], INT16_MAX, INT16_MAX, INT16_MAX));
        }
        if (!(current.cell->checkWall(RIGHT)))
        {
            x = getIndex(current.cell->x + 1, current.cell->y);
            if (x != -1)
                current.itsneighbours.push_back(Star(&maze.cells[x], INT16_MAX, INT16_MAX, INT16_MAX));
        }

        /*
            check if the end of the maze is reached
        */

        if (current == end)
        {
            Star *temp = current.previous;
            while (!(*temp == start)) // back track to the start from end cell
            {
                temp->cell->isPath = true;
                temp->cell->display();
                temp = temp->previous;
                refresh();
            }
            printw("   DONE!!"); /*---/fɪˈniːtəʊ/---*/
            break;
        }

        /*
            iterate over open set to remove current cell from open set
        */
        vector<Star>::iterator it;
        int i;
        for (it = openSet.begin(), i = 0; it <= openSet.end(); it++, i++)
        {
            if (openSet[i] == current)
            {
                openSet.erase(it);
            }
        }
        closedSet.push_back(current); // add current cell to closed list

        // int high_f = INT16_MAX, high_neb = 0;

        for (int i = 0; i < current.itsneighbours.size(); i++) // traverse over all the neighbours of the current cell
        {
            bool inOpen = false, inClose = false;
            Star neigh = current.itsneighbours[i];

            for (int j = 0; j < closedSet.size(); j++)
            {
                if (neigh == closedSet[j])
                {
                    inClose = true;
                    break;
                }
            }

            if (!inClose)   //if the neighbour is not visited before

            {
                neigh.previous = new Star();
                *neigh.previous = current;
                int tempg = current.g_score + 1;
                int j = 0;
                for (j = 0; j < openSet.size(); j++)
                {
                    if (neigh == openSet[j])
                    {
                        inOpen = true;
                        break;
                    }
                }
                if (inOpen)         //and is in open list
                {
                    if (tempg < openSet[j].g_score) //then check for g_score 
                    {
                        openSet[j].g_score = tempg; //and update
                    }
                    end.cell->isOpen = true;
                }
                else            //update values
                {
                    neigh.g_score = tempg;
                    neigh.cell->isOpen = true;
                    neigh.h_score = h(*neigh.cell, *end.cell);
                    neigh.f_score = neigh.g_score + neigh.h_score;
                    openSet.push_back(neigh);
                }
            }
            /*
                these stuffs to display shortest path from start to current in each cycle
            */
            Star *temp = &current;
            while (!(*temp == start))
            {
                temp->cell->isPath = true;
                temp->cell->display();
                temp->cell->isPath = false;

                temp = temp->previous;
            }
            refresh();
            for (int i = 0; i < closedSet.size(); i++)
            {
                closedSet[i].cell->display();
            }
            refresh();
            inOpen = false;
        }
        count++;
        int mx, my;
        getmaxyx(stdscr, my, mx);
        mvprintw(my - 0 - 1, 0, "g_score = %ld, h_score = %ld, f_score = %ld, count = %d", current.g_score, current.h_score, current.f_score, count);
    }
}
