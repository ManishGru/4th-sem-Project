#include <iostream>


#include "cell.cpp"

class Bot
{
private:
    Cell *start;
    Cell *end;
    Cell now;
    // std::vector<Cell *> itsneighbours;

public:
    Bot(Cell *start, Cell *end)
    {
        this->start = start;
        this->end = end;
        now = *start;
    }
    Bot(int x, int y)
    {
        this->start->x = x;
        this->start->y = y;
    }
    void move(int8_t dir)
    {
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
    void sense(int cell)
    {
    }

    // void addNeighbour()
    // {
    //     Cell cell = now;
    //     if ((cell.walls & TOP))
    //     {
    //             this->itsneighbours.push_back((cell->x, cell->y - 1)]);
    //     }
    //     if (cell->checkWall(BOTTOM))
    //     {
    //         cell->itsneighbours.push_back(&this->cells[this->getIndex(cell->x, cell->y + 1)]);
    //     }
    //     if (cell->checkWall(LEFT))
    //     {
    //         cell->itsneighbours.push_back(&this->cells[this->getIndex(cell->x - 1, cell->y)]);
    //     }
    //     if ((cell->checkWall(RIGHT)))
    //     {
    //         cell->itsneighbours.push_back(&this->cells[this->getIndex(cell->x + 1, cell->y)]);
    //     }
    };