
#include "Grid.hpp"
#include "Cell.hpp"

template class Grid<Cell>;

template <typename T>
Grid<T>::Grid(int length) {
    grid = vector<vector<T>>(length, vector<T>(length));
}

template <typename T>
bool Grid<T>::in_bounds(Loc loc) const {
    return loc.row() >= 0 && loc.row() < length() &&
           loc.col() >= 0 && loc.col() < length();
}

template <typename T>
T& Grid<T>::operator[](Loc loc) {
    if (!in_bounds(loc))
        throw "Loc is out of bounds";
    return grid[loc.row()][loc.col()];
}

template <typename T>
int Grid<T>::length() const {
    return grid.size();
}
