
#include "pattern.hpp"

#include <string>
#include <vector>

#include "parser.hpp"
#include "Gen.hpp"
#include "Loc.hpp"

using namespace std;

namespace pattern {
    Gen parse_gen(vector<string> grid_lines) {
        unordered_set<Loc, LocHash> alive_cells;
        
        for (int row = 0; row < grid_lines.size(); row++) {
            for (int col = 0; col < grid_lines[row].size(); col++) {
                if (grid_lines[row][col] != '.') {
                    alive_cells.insert(Loc(row, col));
                }
            }
        }
        return Gen(alive_cells);
    }

    Gen random_gen(int height, int width, int percent_alive) {
        unordered_set<Loc, LocHash> alive_cells;
        int num_cells = height * width;
        int num_alive = (num_cells * percent_alive) / 100;

        for (int i = 0; i < num_alive; i++) {
            int row = rand() % height;
            int col = rand() % width;
            alive_cells.insert(Loc(row, col));
        }

        return Gen(alive_cells);
    }
}
