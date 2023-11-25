
#include "Loc.hpp"
#include <functional>

using namespace std;

Loc::Loc(): x(0), y(0) {}

Loc::Loc(int x, int y): x(x), y(y) {}

int Loc::col() const {
    return this->x;
}

int Loc::row() const {
    return this->y;
}

Loc Loc::operator+(const Loc& other) const {
    return Loc(this->x + other.x, this->y + other.y);
}

Loc Loc::operator-(const Loc& other) const {
    return Loc(this->x - other.x, this->y - other.y);
}

bool Loc::operator==(const Loc& other) const {
    return this->x == other.x && this->y == other.y;
}

vector<Loc> Loc::neighbors() const {
    vector<Loc> neighbors;
    // 8 neighbors
    // 1 2 3
    // 4 X 5
    // 6 7 8
    
    neighbors.push_back(Loc(this->x - 1, this->y - 1));
    neighbors.push_back(Loc(this->x, this->y - 1));
    neighbors.push_back(Loc(this->x + 1, this->y - 1));
    neighbors.push_back(Loc(this->x - 1, this->y));
    neighbors.push_back(Loc(this->x + 1, this->y));
    neighbors.push_back(Loc(this->x - 1, this->y + 1));
    neighbors.push_back(Loc(this->x, this->y + 1));
    neighbors.push_back(Loc(this->x + 1, this->y + 1));
    
    return neighbors;
}

size_t LocHash::operator()(const Loc& loc) const {
    return (hash<int>()(loc.row()) * 7) ^ hash<int>()(loc.col());
}
