
#ifndef GAME_LIFE_HPP
#define GAME_LIFE_HPP

#include <list>
#include <ostream>

#include "Controller.hpp"
#include "Gen.hpp"
#include "Loc.hpp"

#include "Grid.hpp"
#include "Cell.hpp"


using namespace std;

namespace game_life {
    int const REMEMBERED_GENS = 100;

    class GameLife {
        private:
            Gen history[REMEMBERED_GENS];
            int current_gen;
            Controller controls;

        public:
            GameLife(Gen initial_state, int height = 20, int width = 20);

            void add_gen(Gen const& gen);
            Gen get_current_gen() const;
            void print_view(ostream& out, View view);

            void run(ostream& out);
    };
}

#endif
