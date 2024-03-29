#include <iostream>
#include "./maze.cpp"
#include "./maze_dijkstra.cpp"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

#define Astric
#define _dijkstra
int rows = 13, cols = 41; // 40 & 190

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

    maze.display();
    maze.generateMaze();
    maze.display();
    getch();
    refresh();

#ifdef _dijkstra
    dijkstra dijkstra(rows, cols, maze);
    dijkstra.shortPath();
    refresh();
    getch(); 
#endif

#ifdef Astric
    maze.display();
    refresh();
    aStar(maze, true);
    usleep(2000000);

    getch();
    refresh();
    maze.display();
    usleep(1400000);

    aStar(maze, false);

#endif

    refresh();
    getch();
    endwin();
    return 0;
}
