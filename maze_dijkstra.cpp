#include "./maze.cpp"
#include "./cell.cpp"
#include <vector>
#include <bits/stdc++.h>

class dijkstra
{
public:
    int x, y;
    Cell cell;
    dijkstra() {}
    Maze maze;
    std::vector<Cell *> neighbours;
    dijkstra(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void shortPath(std::vector<std::vector<int>> *g);
    void findneighbour(std::vector<Cell *> *neighbours, Cell *current, std::vector<std::vector<int>> *g, std::vector<int> *value, std::vector<bool> *processed);
    Cell *selectMinCell(std::vector<int> &value, std::vector<bool> &processed);
};

Cell *dijkstra::selectMinCell(std::vector<int> &value, std::vector<bool> &processed)
{
    int minimum = INT_MAX;
    Cell *minCell;

    for (int i = 0; i < x * y - 1; i++)
    {
        if (processed[i] == false && value[i] <= minimum)
        {
            minCell = &maze.cells[i];
            minimum = value[i];
        }
    }
    return minCell;
}

void dijkstra::shortPath(std::vector<std::vector<int>> *g)
{
    int total_cells = x * y;
    int countCellvisited = -1;
    std::vector<int> value(total_cells, INT_MAX);
    std::vector<bool> processed(total_cells, false);

    // for debugging
    getmaxyx(stdscr, my, mx);
    last = 0;

    int parentCell[total_cells];
    for (int i = 0; i < total_cells - 1; i++)
    {
        parentCell[i] = -1;
    }
    // std::vector<int> value(total_cells, INT_MAX);
    // std::vector<bool> processed(total_cells, false);
    // std::vector<Cell *> neighbours;

    value[0] = 0;

    Cell *U;
    U = &maze.cells[0];
    maze.endcell;

    bool isLoop = false;

    while (!isLoop)
    {
        neighbours.clear();
        U = selectMinCell(value, processed);
        countCellvisited += 1;
        int Uidx = maze.getIndex(U->x, U->y);

        findneighbour(&neighbours, U, g, &value, &processed);
        processed[Uidx] = true;

        Cell *nextCell;
        while (neighbours.size() > 0)
        {
            nextCell = neighbours.back();
            neighbours.pop_back();
            int neighidx = maze.getIndex(nextCell->x, nextCell->y);

            // tracking stops if endCell found
            // step 5
            // if (neighidx == x * y - 1)
            // {
            //     isLoop = true;
            // }

            value[Uidx] = countCellvisited;
            (*g)[0][neighidx] = value[Uidx] + value[neighidx];
            if ((*g)[Uidx][neighidx] != 0 && (int)processed[neighidx] == false && value[Uidx] != INT_MAX && value[Uidx] + (*g)[Uidx][neighidx] >= value[neighidx])
            {
                parentCell[neighidx] = Uidx;
            }
        }
        int count = 0;
        for (int i = 0; i < total_cells; i++)
        {
            if (processed[i] == true)
            {
                count++;
            }
        }
        if (count == total_cells - 1)
        {
            isLoop = true;
        }
    }
    int displayCellidx;
    Cell displayCell;
    int ptIdx = (int)parentCell[total_cells - 1];
    for (int i = (int)(*g)[0][total_cells - 1]; i > 0; --i)
    {
        if (ptIdx != -1)
        {
            displayCell = maze.cells[ptIdx];
            displayCell.dijsktrashortPath = true;
            displayCell.display();
            ptIdx = (int)parentCell[ptIdx];
        }
    }
    displayCell = maze.cells[x * y - 1];
    displayCell.isEnd = true;
    displayCell.display();
}

void dijkstra::findneighbour(std::vector<Cell *> *neighbours, Cell *current, std::vector<std::vector<int>> *g, std::vector<int> *value, std::vector<bool> *processed)
{
    int currentidx = maze.getIndex(current->x, current->y);
    refresh();
    // top
    if (!(current->checkWall(TOP)))
    {
        int topidx = maze.getIndex(current->x, current->y - 1);
        if (topidx != -1)
        {
            if ((*processed)[topidx] == false)
            {
                Cell *top = &maze.cells[topidx];
                top->neighbours = true;
                top->display();
                usleep(2000);
                (*value)[topidx] = 1;
                (*g)[currentidx][topidx] = 1;
                (*neighbours).push_back(top);
            }
        }
    }
    // bottom
    if (!(current->checkWall(BOTTOM)))
    {
        int bottomidx = maze.getIndex(current->x, current->y + 1);
        if (bottomidx != -1)
        {
            if ((*processed)[bottomidx] == false)
            {
                Cell *bottom = &maze.cells[bottomidx];
                bottom->neighbours = true;
                bottom->display();
                usleep(2000);
                (*value)[bottomidx] = 1;
                (*g)[currentidx][bottomidx] = 1;
                (*neighbours).push_back(bottom);
            }
        }
    }
    // right
    if (!(current->checkWall(RIGHT)))
    {
        int rightidx = maze.getIndex(current->x + 1, current->y);
        if (rightidx != -1)
        {
            if ((*processed)[rightidx] == false)
            {
                Cell *right = &maze.cells[rightidx];
                right->neighbours = true;
                right->display();
                usleep(2000);
                (*value)[rightidx] = 1;
                (*g)[currentidx][rightidx] = 1;
                (*neighbours).push_back(right);
            }
        }
    }
    // left
    if (!(current->checkWall(LEFT)))
    {
        int leftidx = maze.getIndex(current->x - 1, current->y);
        if (leftidx != -1)
        {
            if ((*processed)[leftidx] == false)
            {
                Cell *left = &maze.cells[leftidx];
                left->neighbours = true;
                left->display();
                usleep(2000);
                (*value)[leftidx] = 1;
                (*g)[currentidx][leftidx] = 1;
                (*neighbours).push_back(left);
            }
        }
    }
}

int main()
{
    std::srand(std::time(nullptr));
    initscr();
    raw();
    int x = 13, y = 41;
    dijkstra dijkstra(x, y);
    dijkstra.maze = Maze(x, y);

    system("clear");
    start_color();

    dijkstra.maze.generateMaze();

    std::vector<std::vector<int>> g((x - 1) * (x - 1) * (y - 1) * (y - 1), std::vector<int>(x, 0));
    dijkstra.shortPath(&g);

    refresh();
    getch();
    endwin();
    return 0;
}