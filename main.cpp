#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>
#include <ctime>

// private includes
#include "./src/maze.cpp"
#include "./src/maze_dijkstra.cpp"
#include "./src/bot.cpp"
#include "./src/astar.cpp"



// #define Astric
// #define _dijkstra
int rows = 30, cols = 20;


int main()
{

    

    std::srand(std::time(nullptr));
    // initscr();
    // raw();
    Maze maze(rows, cols);

    // system("clear");
    // start_color();

    maze.generateMaze();
    // maze.display();
    // refresh();

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

    // refresh();
    // getch();
    // endwin();
    maze.display3d();
    return 0;
}
