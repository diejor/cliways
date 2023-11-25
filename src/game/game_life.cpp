#include <chrono>
#include <thread>
#include <cstdlib>

#include <ncurses.h>


#include "Cell.hpp"
#include "game_life.hpp"

#include "Grid.hpp"
#include "Loc.hpp"

#include "output.hpp"

using namespace std;

namespace game_life {
    bool is_alive(Generation state, Loc loc) {
        return state.find(loc) != state.end();
    }

    Generation next_state(
            Generation current_state, 
            int alive_bound = 2, 
            int dead_bound = 4, 
            int reproduction = 3) {
        Generation next_state;

        for (Loc alive : current_state) {
            int alive_count = 0;
            for (Loc neighbor : alive.neighbors()) {
                if (is_alive(current_state, neighbor)) {
                    // neighbor is alive
                    alive_count++;
                } else {
                    // neighbor is dead
                    // check if neighbor can be reproduced
                    // by counting the number of alive parents

                    int parent_count = 0;
                    // at least 1 parent is alive since it comes
                    // from an alive neighbor
                    for (Loc parent : neighbor.neighbors()) {
                        if (is_alive(current_state, parent)) {
                            parent_count++;
                        }
                    }
                    if (parent_count == reproduction) {
                        next_state.insert(neighbor);
                    }
                }
            }
            
            if (alive_count >= alive_bound && alive_count < dead_bound) {
                next_state.insert(alive);
            }
        }

        return next_state;
    }

    Grid<Cell> simple_view(Generation state, int size) {
        Grid<Cell> view(size);
        
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {

                Loc loc(row, col);
                if (is_alive(state, loc)) {
                    view[loc] = Cell{true};
                }
            }
        }

        return view;
    }

    void print_view(Grid<Cell> view) {
        for (int row = 0; row < view.length(); row++) {
            for (int col = 0; col < view.length(); col++) {
                Loc loc(row, col);
                cout << (view[loc].alive ? "O " : ". ");
            }
            cout << endl;
        }
    }

    GameLife::GameLife(Generation initial_state, int generations_per_second) {
        this->history.push_back(initial_state);
        this->generations_per_second = generations_per_second;
    }

    void GameLife::run() {
        while (true) {
            system("clear");
            cout << "Running Game of Life" << endl;
            cout << "Press Ctrl+C to stop" << endl;

            Grid<Cell> view = simple_view(history.back(), 10);
            print_view(view);

            // sleep ms between generations_per_second
            int sleep_ms = 1000 / generations_per_second;
        
            this_thread::sleep_for(chrono::milliseconds(sleep_ms));

            history.push_back(next_state(history.back()));
        }
    }

}
