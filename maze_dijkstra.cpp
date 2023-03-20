#include "./maze.cpp"
#include "./cell.cpp"
#include <vector>
#include <bits/stdc++.h>

class dijkstra
{
public:
    int x, y;
    Cell cell;
    Maze maze;
    std::vector<std::vector<int>> g;
    dijkstra(int p, int q, Maze &m)
    {
        x = p;
        y = q;
        maze = m;
        g = std::vector<std::vector<int>>(x * y, std::vector<int>(x * y, INT_MAX));
    }
    Cell *selectMinCell(std::vector<bool> &processed);
    void findneighbour(std::vector<Cell *> *neighbours, Cell *current);
    void shortPath();
};

Cell *dijkstra::selectMinCell(std::vector<bool> &processed)
{
    int minimum = INT_MAX;
    Cell *minCell;
    for (int i = 0; i < x * y - 1; i++)
    {
        if (processed[i] == false && g[maze.getIndex(maze.startcell->x, maze.startcell->y)][i] <= minimum)
        {
            minCell = &maze.cells[i];
            minimum = g[maze.getIndex(maze.startcell->x, maze.startcell->y)][i];
        }
    }
    return minCell;
}

void dijkstra::findneighbour(std::vector<Cell *> *neighbours, Cell *current)
{
    int currentidx = maze.getIndex(current->x, current->y);
    refresh();
    // top
    if (!(current->checkWall(TOP)))
    {
        int topidx = maze.getIndex(current->x, current->y - 1);
        if (topidx != -1)
        {
            Cell *top = &maze.cells[topidx];
            top->isOpen = true;
            top->display();
            usleep(200);
            g[currentidx][topidx] = 1;
            (*neighbours).push_back(top);
        }
    }
    // bottom
    if (!(current->checkWall(BOTTOM)))
    {
        int bottomidx = maze.getIndex(current->x, current->y + 1);
        if (bottomidx != -1)
        {
            Cell *bottom = &maze.cells[bottomidx];
            bottom->isOpen = true;
            bottom->display();
            usleep(200);
            g[currentidx][bottomidx] = 1;
            (*neighbours).push_back(bottom);
        }
    }
    // right
    if (!(current->checkWall(RIGHT)))
    {
        int rightidx = maze.getIndex(current->x + 1, current->y);
        if (rightidx != -1)
        {
            Cell *right = &maze.cells[rightidx];
            right->isOpen = true;
            right->display();
            usleep(200);
            g[currentidx][rightidx] = 1;
            (*neighbours).push_back(right);
        }
    }
    // left
    if (!(current->checkWall(LEFT)))
    {
        int leftidx = maze.getIndex(current->x - 1, current->y);
        if (leftidx != -1)
        {
            Cell *left = &maze.cells[leftidx];
            left->isOpen = true;
            left->display();
            usleep(200);
            g[currentidx][leftidx] = 1;
            (*neighbours).push_back(left);
        }
    }
}

void dijkstra::shortPath()
{
    int total_cells = x * y;
    int countCellvisited = -1;

    std::vector<bool> processed(total_cells, false);
    int parentCell[total_cells] = {-1};

    // for debugging
    getmaxyx(stdscr, my, mx);
    last = 0;

    g[maze.getIndex(maze.startcell->x, maze.startcell->y)][maze.getIndex(maze.startcell->x, maze.startcell->y)] = 0;
    Cell *U;
    U = maze.startcell;

    // int idxu = maze.getIndex(U->x, U->y);
    // mvprintw(my - last - 1, 0, "%d", idxu);

    bool isLoop = false, selected = false;
    int count = 0;

    while (!isLoop)
    {
        std::vector<Cell *> neighbours;
        U = selectMinCell(processed);
        Cell start;

        int Uidx = maze.getIndex(U->x, U->y);

        findneighbour(&neighbours, U);

        Cell *nextCell;
        while (neighbours.size() > 0)
        {
            nextCell = neighbours.back();
            neighbours.pop_back();
            int neighidx = maze.getIndex(nextCell->x, nextCell->y);

            // tracking stops if endCell found
            if (neighidx == maze.getIndex(maze.endcell->x, maze.endcell->y))
            {
                isLoop = true;
            }

            if ((int)processed[neighidx] == true)
            {
                if ((g[maze.getIndex(maze.startcell->x, maze.startcell->y)][Uidx] + 1) < g[maze.getIndex(maze.startcell->x, maze.startcell->y)][neighidx])
                {
                    g[maze.getIndex(maze.startcell->x, maze.startcell->y)][neighidx] = g[maze.getIndex(maze.startcell->x, maze.startcell->y)][Uidx] + 1;

                    parentCell[neighidx] = Uidx;
                }
                continue;
            }
            g[maze.getIndex(maze.startcell->x, maze.startcell->y)][neighidx] = g[maze.getIndex(maze.startcell->x, maze.startcell->y)][Uidx] + 1;
            parentCell[neighidx] = Uidx;
        }
        processed[Uidx] = true;
        count++;
        if (count == total_cells - 1)
        {
            isLoop = true;
        }
    }
    int displayCellidx;
    Cell displayCell;
    int ptIdx = (int)parentCell[maze.getIndex(maze.endcell->x, maze.endcell->y)];
    for (int i = (int)g[maze.getIndex(maze.startcell->x, maze.startcell->y)][maze.getIndex(maze.endcell->x, maze.endcell->y)]; i > 0; --i)
    {
        if (ptIdx != -1)
        {
            displayCell = maze.cells[ptIdx];
            // Display the Shortest Path
            displayCell.isPath = true;
            displayCell.display();
            ptIdx = (int)parentCell[ptIdx];
            if (ptIdx == maze.getIndex(maze.startcell->x, maze.startcell->y))
            {
                break;
            }
        }
    }
}