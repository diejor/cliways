
#ifndef CELL_HPP
#define CELL_HPP

#include "Loc.hpp"

struct Cell {
    Loc loc;
    bool alive;

    Cell() {
        this->loc = Loc(0, 0);
        this->alive = false;
    }

    Cell(Loc loc, bool alive) {
        this->loc = loc;
        this->alive = alive;
    }
};

#endif // !CELL_HPP
