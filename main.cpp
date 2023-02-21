#include <iostream>
#include "./maze.cpp"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "./bot.cpp"
#include "./astar.cpp"
#include <unistd.h>
#define A *
int main()
{
    std::srand(std::time(nullptr));
    initscr();
    raw();

    Maze maze(20, 20);

    system("clear");
    start_color();

    maze.generateMaze();
    maze.display();

#ifdef A *
    aStar(maze, true);
    usleep(2000000);
    refresh();
    // maze.display();
    aStar(maze, false);
#endif

    refresh();
    getch();
    endwin();
    return 0;
}
