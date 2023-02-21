#include <queue>
#include <iostream>
#include "./cell.cpp"
#include "./maze.cpp"
#include <unistd.h>
// #include "./bot.cpp"

using namespace std;

int ROWS, COLS;
/*---------------------------------------*/
class Star
{
public:
    Cell *cell;
    int g_score;
    int h_score;
    int f_score;
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

    inline bool operator==(Star s)
    {
        if ((s.cell->x == cell->x) && (s.cell->y == cell->y))
            return 1;
        else
            return 0;
    }

    inline int getIndex()
    {
        if (cell->x < 0 || cell->y < 0 || this->cell->x > ROWS - 1 || cell->y > COLS - 1)
        {
            return -1;
        }
        return cell->x + cell->y * COLS;
    }
};
/*---------------------------------------*/
inline int getIndex(int x, int y)
{
    if (x < 0 || y < 0 || x > COLS - 1 || y > ROWS - 1)
    {
        return -1;
    }
    return x + y * COLS;
}
inline int h(Cell c1, Cell c2)
{
    return (abs(c1.x - c2.x) + abs(c1.y - c2.y));
}

/*---------------------------------------*/

void aStar(Maze &maze, int check)
{
    ROWS = maze.rows, COLS = maze.cols;
    int s = maze.getIndex(maze.startcell->x, maze.startcell->y);
    int e = maze.getIndex(maze.endcell->x, maze.endcell->y);
    Star end(maze.endcell, INT16_MAX, INT16_MAX, INT16_MAX);
    Star start(maze.startcell, 0, 0, 0);

    vector<Star> openSet;
    vector<Star> closedSet;
    openSet.push_back(start);

    int count = 0;
    while (1)
    {
        int winner = 0;
        if (openSet.size() == 0)
        {
            printw("nosolution!!!");
            return;
        }
        for (int i = 0; i < openSet.size(); i++)
        {
            if (check)
            {
                if (openSet[i].h_score < openSet[winner].h_score)
                {
                    winner = i;
                }
            }
            else
            {
                if (openSet[i].f_score < openSet[winner].f_score)
                {
                    winner = i;
                }
            }
        }
        Star current = openSet[winner];
        /*-----------------------------------------------*/
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

        // for (int i = 0; i < current.itsneighbours.size(); i++)
        // {
        //     current.itsneighbours[i].cell->isOpen = true;
        // }
        /*---------------------------------------------*/

        if (current == end)
        {
            Star *temp = current.previous;
            // usleep(20000);
            while (!(*temp == start))
            {
                temp->cell->isPath = true;
                temp->cell->display();
                temp = temp->previous;
                // usleep(10000);
                refresh();
            }
            printw("   DONE!!");
            break;
        }
        /*---------------------------------------------*/

        vector<Star>::iterator it;
        int i;
        for (it = openSet.begin(), i = 0; it <= openSet.end(); it++, i++)
        {
            if (openSet[i] == current)
            {
                openSet.erase(it);
            }
        }
        closedSet.push_back(current);

        int high_f = INT16_MAX, high_neb = 0;
        for (int i = 0; i < current.itsneighbours.size(); i++)
        {
            // }
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
            if (!inClose)
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
                if (inOpen)
                {
                    if (tempg < openSet[j].g_score)
                    {
                        openSet[j].g_score = tempg;
                    }
                    end.cell->isOpen = true;
                }
                else
                {

                    neigh.g_score = tempg;
                    neigh.cell->isOpen = true;
                    neigh.h_score = h(*neigh.cell, *end.cell);
                    neigh.f_score = neigh.g_score + neigh.h_score;
                    openSet.push_back(neigh);
                }

                // neigh.h_score = h(*neigh.cell, *end.cell);
                // neigh.f_score = neigh.g_score + neigh.h_score;
            }

            Star *temp = &current;
            while (!(*temp == start))
            {
                temp->cell->isPath = true;
                temp->cell->display();
                temp->cell->isPath = false;

                temp = temp->previous;
            }
            refresh();
            // usleep(1000);
            // neigh.cell->display();

            for (int i = 0; i < closedSet.size(); i++)
            {
                // usleep(10);
                closedSet[i].cell->display();
            }
            refresh();
        }
        count++;
        int mx, my;
        getmaxyx(stdscr, my, mx);
        mvprintw(my - 0 - 1, 0, "g_score = %ld, h_score = %ld, f_score = %d, count = %d", current.g_score, current.h_score, current.g_score, count);
    }
}
