#include <iostream>
#include <unordered_set>

using namespace std;

#include "input.hpp"
#include "output.hpp"

#include "game_life.hpp"

int main() {
    Generation initial_state = {
        Loc(5, 0),
        Loc(5, 1),
        Loc(5, 2),
        Loc(5, 3),
        Loc(5, 4),
        Loc(5, 5),
        Loc(5, 6),
        Loc(5, 7),
        Loc(5, 8),
        Loc(5, 9),
           };

    game_life::GameLife game(initial_state, 2);
    game.run();
    return 0;
}
