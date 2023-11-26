
#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

#include "Loc.hpp"

using namespace std;


template <typename T>
class Grid {
    private:
        vector<vector<T>> grid;
    public:
        Grid(int size);
        Grid(int height, int width);

        bool in_bounds(Loc loc) const;
    
        T& operator[](Loc loc);
        
        int height() const;
        int width() const;
};


#endif // !GRID_HPP
