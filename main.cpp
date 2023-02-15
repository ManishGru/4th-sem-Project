#include <iostream>
#include "./maze.cpp"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "./bot.cpp"
int main()
{
    std::srand(std::time(nullptr));
    initscr();
    raw();

    Maze maze(13, 41);
    Bot bot(maze.cells[0], maze.cells[1]);

    system("clear");
    start_color();

    maze.display();
    maze.generateMaze();

    refresh();
    getch();
    endwin();
    return 0;
}
