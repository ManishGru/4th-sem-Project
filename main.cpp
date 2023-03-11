#include <iostream>
#include "./maze.cpp"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "./bot.cpp"
#include "./astar.cpp"
#include <unistd.h>
#define A //`1*9/////////*
int main()
{
    std::srand(std::time(nullptr));
    initscr();
    raw();

    Maze maze(20, 30);

    system("clear");
    start_color();

    maze.generateMaze();
    maze.display();
    refresh();

#ifdef A
    // aStar(maze, true);
    usleep(1400000);

    system("clear");
    start_color();

    maze.genMazeAgain();
    // maze.generateMaze();

    refresh();
    maze.display();
    // aStar(maze, false);

#endif

    refresh();
    getch();
    endwin();
    return 0;
}
