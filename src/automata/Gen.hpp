
#ifndef GEN_HPP
#define GEN_HPP

#include <unordered_set>

#include "Loc.hpp"

class Gen {
    private: 
        unordered_set<Loc, LocHash> alive_cells;
    
    public:
        Gen();
        Gen(unordered_set<Loc, LocHash> const& alive_cells);
        bool is_alive(Loc loc) const;
        void toggle(Loc loc);
        Gen next_gen(int alive_bound = 2, int dead_bound = 4, int reproduction = 3) const;
};

#endif // !GEN_HPP
