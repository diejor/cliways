#include <ostream>

#include <curses.h>
#include <ncurses.h>

#include "Cell.hpp"
#include "Controller.hpp"
#include "game_life.hpp"

#include "Grid.hpp"
#include "Loc.hpp"

#include "output.hpp"

using namespace std;

namespace game_life {

    GameLife::GameLife(Gen initial_state, int height, int width) :
        controls(Controller(height, width)) {
        add_gen(initial_state);
    }

    void GameLife::add_gen(Gen const& gen) {
        current_gen = (current_gen + 1) % REMEMBERED_GENS;
        history[current_gen] = gen;
    }

    void GameLife::print_view(ostream& out, View view) {
        Gen current_gen = history[this->current_gen];
        for (int row = 0; row < view.height; row++) {
            for (int col = 0; col < view.width; col++) { 
                Loc loc(row, col);
                if (current_gen.is_alive(loc + view.start_loc)) {
                    out << "o ";
                } else {
                    out << ". ";
                }
            }
            out << endl;
        }
    }

    void GameLife::run(ostream& out) {
        controls.init_ncurses();

        while (!controls.exit) {

            controls.handle_input();
            
            if (!controls.paused) { 
                Gen next_gen = history[current_gen].next_gen();
                add_gen(next_gen);
            }

            controls.toggle_clicks(history[current_gen]);

            system("clear");

            print_view(cout, controls.view);
            cout << "Generations per second: " << controls.generations_per_second << 
                " | " << (controls.paused ? "PAUSED" : "Running") << endl;
            cout << endl;
            cout << "\t Controls: " << endl;
            cout << "\t: arrows to move view" << endl;
            cout << "\t: 'u' to speed up" << endl;
            cout << "\t: 'd' to slow down" << endl;
            cout << "\t: 'space' to pause" << endl;
            cout << "\t: '=' to expand view" << endl;
            cout << "\t: '-' to reduce view" << endl;
            cout << "\t: mouse click to toggle cell" << endl;
            cout << "\t: 'q' to quit" << endl;
            

            controls.wait();
        }
    }

}
