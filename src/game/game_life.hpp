
#ifndef GAME_LIFE_HPP
#define GAME_LIFE_HPP

#include <list>
#include <unordered_set>

#include "Loc.hpp"

using namespace std;

using Generation = unordered_set<Loc, LocHash>;

namespace game_life {

    class GameLife {
        private:
            list<Generation> history;
            int generations_per_second;

        public:
            GameLife();

            GameLife(Generation initial_state, int generations_per_second = 1);

            void run();
    };
}

#endif
