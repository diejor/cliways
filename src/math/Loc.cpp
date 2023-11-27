
#include "Loc.hpp"
#include <functional>

using namespace std;

Loc::Loc(): row(0), col(0) {}

Loc::Loc(int r, int c): row(r), col(c) {}

int Loc::get_row() const {
    return this->row;
}

int Loc::get_col() const {
    return this->col;
}

Loc Loc::operator+(const Loc& other) const {
    return Loc(this->row + other.get_row(), this->col + other.get_col());
}

Loc Loc::operator-(const Loc& other) const {
    return Loc(this->row- other.get_row(), this->col- other.get_col());
}

bool Loc::operator==(const Loc& other) const {
    return this->row == other.get_row() && this->col == other.get_col();
}

Loc& Loc::operator+=(const Loc& other) {
    this->row += other.get_row();
    this->col += other.get_col();
    return *this;
}

vector<Loc> Loc::neighbors() const {
    vector<Loc> neighbors;
    // 8 neighbors
    // 1 2 3
    // 4 X 5
    // 6 7 8
    
    neighbors.push_back(Loc(this->row - 1, this->col - 1));
    neighbors.push_back(Loc(this->row - 1, this->col));
    neighbors.push_back(Loc(this->row - 1, this->col + 1));
    neighbors.push_back(Loc(this->row, this->col - 1));
    neighbors.push_back(Loc(this->row, this->col + 1));
    neighbors.push_back(Loc(this->row + 1, this->col - 1));
    neighbors.push_back(Loc(this->row + 1, this->col));
    neighbors.push_back(Loc(this->row + 1, this->col + 1));
    
    return neighbors;
}

size_t LocHash::operator()(const Loc& loc) const {
    return (hash<int>()(loc.get_row()) * 7) ^ hash<int>()(loc.get_col());
}
