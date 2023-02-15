#include <iostream>
#include "./cell.cpp"

class Bot
{
private:
    Cell start;
    Cell end;
    Cell now;
public:
    Bot(Cell start, Cell end){
        this->start = start;
        this->end = end;
    }
    Bot(int x, int y)
    {
        this->start.x = x;
        this->start.y = y;
    }
    void move(int8_t dir)
    {
        Cell now;
        switch (dir)
        {
        case LEFT:
            now.x = now.x - 1;
            break;
        case RIGHT:
            now.x = now.x + 1;
            break;
        case TOP:
            now.y = now.y - 1;
            break;
        case BOTTOM:
            now.y = now.y + 1;
            break;
        default:
            break;
        }
    }
    void sense(int cell){

    }
};