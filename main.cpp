#include <iostream>
#include "./maze.cpp"
#include "./maze_dijkstra.cpp"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

#define _dijkstra
int rows = 13, cols = 41;

int main()
{
    std::srand(std::time(nullptr));
    initscr();
    raw();
    Maze maze(rows, cols);

    system("clear");
    start_color();

    maze.generateMaze();

#ifdef _dijkstra
    dijkstra dijkstra(rows, cols, maze);
    dijkstra.shortPath();

#endif

    refresh();
    getch();
    endwin();
    return 0;
}
