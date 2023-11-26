
#include "Grid.hpp"
#include "Cell.hpp"

template class Grid<Cell>;

template <typename T>
Grid<T>::Grid(int size) {
    grid = vector<vector<T>>(size, vector<T>(size));
}

template <typename T>
Grid<T>::Grid(int height, int width) {
    grid = vector<vector<T>>(height, vector<T>(width));
}

template <typename T>
bool Grid<T>::in_bounds(Loc loc) const {
    return loc.get_row() >= 0 && loc.get_row() < height() &&
           loc.get_col() >= 0 && loc.get_col() < width();
}

template <typename T>
T& Grid<T>::operator[](Loc loc) {
    if (!in_bounds(loc))
        throw "Loc is out of bounds";
    return grid[loc.get_row()][loc.get_col()];
}

template <typename T>
int Grid<T>::height() const {
    return grid.size();
}

template <typename T>
int Grid<T>::width() const {
    return grid[0].size();
}
