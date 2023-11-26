#include "Gen.hpp"

#include <vector>

#include "Loc.hpp"

using namespace std;

Gen::Gen() {
    alive_cells = unordered_set<Loc, LocHash>();
}

Gen::Gen(unordered_set<Loc, LocHash> const& alive) {
    alive_cells = unordered_set<Loc, LocHash>(alive);
}

bool Gen::is_alive(Loc loc) const {
    return alive_cells.find(loc) != alive_cells.end();
}

void Gen::toggle(Loc loc) {
    if (is_alive(loc)) {
        alive_cells.erase(loc);
    } else {
        alive_cells.insert(loc);
    }
}

Gen Gen::next_gen(
        int alive_bound,
        int dead_bound,
        int reproduction) const {
    unordered_set<Loc, LocHash> next_alive_cells;

    for (Loc const& alive : alive_cells) {
        int alive_count = 0;
        for (Loc const& neighbor : alive.neighbors()) {
            if (is_alive(neighbor)) {
                // neighbor is alive
                alive_count++;
            } else {
                // neighbor is dead
                // check if neighbor can be reproduced
                // by counting the number of alive parents

                int parent_count = 0;
                // at least 1 parent is alive since it comes
                // from an alive neighbor
                for (Loc const& parent : neighbor.neighbors()) {
                    if (is_alive(parent)) {
                        parent_count++;
                    }
                }
                if (parent_count == reproduction) {
                    next_alive_cells.insert(neighbor);
                }
            }
        }
        
        if (alive_count >= alive_bound && alive_count < dead_bound) {
            next_alive_cells.insert(alive);
        }
    }

    return Gen(next_alive_cells);
}
