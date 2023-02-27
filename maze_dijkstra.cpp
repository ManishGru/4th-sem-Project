#include "./maze.cpp"
#include "./cell.cpp"
#include <vector>
#include <bits/stdc++.h>

int x = 13, y = 41;

class dijkstra
{
public:
    int x, y;
    Maze maze;
    Cell cell;
    // Cell *next;

    dijkstra() {} // the Default Constructor
    dijkstra(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int total_cells = x * y;
    // std::vector<Cell> cells = maze.cells;

    bool isProcessed = false;
    // std::vector<Cell *> neighbours; // Stores the neighbour of the current cell
    // std::vector<Cell *> st; // Create Stack to backtrack the path
    // std::vector<int> value; // Keeps shortest path values to each neighbour Cell from source Cell
    // to infinity for all other nodes.
    // std::vector<bool> processed; // Unvisited Cells called the unvisited Set

    void shortPath(std::vector<std::vector<int>> *g);

    void findneighbour(Cell cell, Maze maze, std::vector<Cell *> *neighbours, Cell *current, std::vector<Cell> cells, std::vector<std::vector<int>> *g, std::vector<int> *value, int *last, std::vector<bool> *processed);
    Cell *selectMinCell(std::vector<int> &value, std::vector<bool> &processed);
};

Cell *dijkstra::selectMinCell(std::vector<int> &value, std::vector<bool> &processed)
{
    int minimum = INT_MAX;
    Cell *minCell = new Cell();

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

    // for debugging
    getmaxyx(stdscr, my, mx);
    last = 5;

    int parentCell[total_cells]; // Stores Shortest Path Structure
    // assign every cell a distance value of INFINITY
    std::vector<int> value(total_cells, INT_MAX); // keeps shortest path values to each cell from source cell
    // mark all cells as unvisited
    std::vector<bool> processed(total_cells, false); // TRUE == Cells is processed
    std::vector<Cell *> neighbours;                  // Stores the neighbour of the current cell

    parentCell[0] = -1; // Start cell has no parent
    value[0] = 0;

    maze.endcell->isEnd = false;

    Cell *U = new Cell();
    bool isLoop = false;

    while (!isLoop)
    {
        neighbours.clear();
        U = selectMinCell(value, processed); // chooses one of the neighbour randomly
        if (maze.getIndex(U->x, U->y) == x * y - 1)
        {
            maze.endcell->isEnd = true;
        }
        int Uidx = maze.getIndex(U->x, U->y);

        findneighbour(cell, maze, &neighbours, U, maze.cells, g, &value, &last, &processed);
        // Displays the initial selected cell
        U->current = true;
        U->display();

        processed[Uidx] = 1;

        Cell *nextCell = new Cell();
        if (neighbours.size() != 0)
        {
            // choose nextCell as random cell
            if (neighbours.size() == 1)
            {
                // mvprintw(my - last - 1, 0, "only one neighbours");
                // last++;
                nextCell = neighbours[0];
            }
            else
            {
                nextCell = neighbours[std::rand() % neighbours.size()];
            }
            int neighidx = maze.getIndex(nextCell->x, nextCell->y);

            // for DEBUGGING
            // mvprintw(my - last - 1, 0, "%d n %d", nextCell->x, nextCell->y);
            // last++;
            // mvprintw(my - last - 1, 0, "Uidx = %d\t neighidx = %d\t g[Uidx][neighidx] = %d\t processed ? %d", Uidx, neighidx, (int)(*g)[Uidx][neighidx], (int)processed[neighidx]);
            // last++;
            // mvprintw(my - last - 1, 0, "value[Uidx] =  %d\t value[neighidx] = %d\t", (int)value[Uidx], (int)value[neighidx]);
            // last++;

            if ((*g)[Uidx][neighidx] != 0 && (int)processed[neighidx] == false && value[Uidx] != INT_MAX && value[Uidx] + (*g)[Uidx][neighidx] <= value[neighidx])
            {
                value[neighidx] = value[Uidx] + (*g)[Uidx][neighidx];
                parentCell[neighidx] = Uidx;
                // mvprintw(my - last - 1, 0, "hello");
                // last++;
            }
            // mvprintw(my - last - 1, 0, "cost(neighidx) = %d\t ptCl[neighidx] = %d\n", (int)value[neighidx], (int)parentCell[neighidx]);
            // last++;
            // Uidx = neighidx;
        }
        // check all is processed or not
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
    // Print Shortest Path graph
    // for (int i = 1; i < total_cells; ++i)
    // {
    //     mvprintw(my - last - 1, 0, "U->V: %d -> %d  wt = %d\n", (int)parentCell[i], i, (int)(*g)[i][i]);
    //     last++;
    // }
}

void dijkstra::findneighbour(Cell cell, Maze maze, std::vector<Cell *> *neighbours, Cell *current, std::vector<Cell> cells, std::vector<std::vector<int>> *g, std::vector<int> *value, int *last, std::vector<bool> *processed)
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
                usleep(5000);
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
                usleep(5000);
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
                usleep(5000);
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
                usleep(5000);
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

    dijkstra dijkstra(x, y);
    dijkstra.cell = Cell(x, y);
    dijkstra.maze = Maze(x, y);

    system("clear");
    start_color();

    dijkstra.maze.generateMaze();
    // assign every cell to cell a distance value of 0
    std::vector<std::vector<int>> g((x - 1) * (x - 1) * (y - 1) * (y - 1), std::vector<int>(x, 0));
    dijkstra.shortPath(&g);
    // dijkstra.maze.display();
    refresh(); // update the screen
    getch();   // wait for user input
    endwin();  // clean up the Curses library
    return 0;
}