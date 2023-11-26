
#ifndef GAME_LIFE_HPP
#define GAME_LIFE_HPP

#include <list>

#include "Gen.hpp"
#include "Loc.hpp"


using namespace std;

namespace game_life {
    int const REMEMBERED_GENS = 100;

    class GameLife {
        private:
            Gen history[REMEMBERED_GENS];
            int current_gen;
            int generations_per_second;

        public:
            GameLife();

            GameLife(Gen initial_state, int generations_per_second = 1);

            void add_gen(Gen const& gen);
            Gen get_current_gen() const;

            void run();
    };
}

#endif
