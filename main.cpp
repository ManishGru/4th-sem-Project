#include <iostream>
#include "./maze.cpp"
#include "./maze_dijkstra.cpp"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

// #define Astric
#define _dijkstra
int rows = 13, cols = 41;

#include "./bot.cpp"
#include "./astar.cpp"
#include <unistd.h>
int main()
{
    std::srand(std::time(nullptr));
    initscr();
    raw();
    Maze maze(rows, cols);

    system("clear");
    start_color();

    maze.generateMaze();
    maze.display();
    refresh();

#ifdef _dijkstra
    dijkstra dijkstra(rows, cols, maze);
    dijkstra.shortPath();
    refresh();

#endif

#ifdef Astric
    maze.display();
    refresh();
    aStar(maze, true);
    usleep(1400000);

    // system("clear");
    // start_color();

    // maze.genMazeAgain();
    // maze.generateMaze();

    refresh();
    // maze.display();
    aStar(maze, false);

#endif

    refresh();
    getch();
    endwin();
    return 0;
}
