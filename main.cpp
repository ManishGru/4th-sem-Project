#include <iostream>
#include "./maze.cpp"
#include <ncurses.h>
int main()
{
    initscr();
    raw();
    int num;
    printw("Enter number of cells:");
    scanw("%d", &num);
    Maze maze(num, num);
    system("clear");
    start_color();
    maze.display();
    maze.generateMaze();
    refresh();
    getch();
    endwin();
    return 0;
}
