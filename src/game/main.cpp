#include <iostream>
#include <unordered_set>

using namespace std;

#include "input.hpp"
#include "output.hpp"

#include "Gen.hpp"
#include "game_life.hpp"

int main() {
   unordered_set<Loc, LocHash> alive = {
        Loc(5, 5),
        Loc(5, 6),
        Loc(5, 7),
        Loc(5, 8),
        Loc(5, 9),
        Loc(5, 10),
        Loc(5, 11), 
        Loc(5, 12),
        Loc(5, 13),
        Loc(5, 14),
    };

    Gen initial_state(alive);

    game_life::GameLife game(initial_state, 5);
    game.run();
    return 0;
}
