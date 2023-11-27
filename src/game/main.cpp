/*
 * Conway's Game of Life
 * file: main.cpp
 * author: Diego R.R. 
 * started: 11/24/2020 
 * course: CS2337.501
 *
 * Purpose: To explore the concepts of cellular automata through Conway's Game of Life
 * and to visualize complex patterns emerging from simple rules.
 *
 * Changelog:
 *  - 11/24 - Set up project structure and base classes for cellular automata
 *  - 11/25 - Added pattern parsing and rendering logic
 *  - 11/26 - Implemented game rules and controller logic
 *  - 11/26 - Added user interaction for controlling the game state and patterns
 *
 * Notes:
 *  - The game's patterns are defined in text files within the resources folder and
 *    are parsed using the parser module in the utils directory.
 *
 *  - The game follows an object-oriented design with clear separation of concerns,
 *    facilitating maintainability and future extensions. Core functionalities like
 *    the game grid, cell generation, and pattern manipulation are encapsulated within
 *    their respective classes and namespaces.
 *
 *  - The structure of the project is organized as follows:
 *    ├── resources
 *    │   └── Life Pattern Files
 *    │       ├── Billiard-Pattern.txt
 *    │       ├── GardenOfEden.txt
 *    │       ├── GosperGliderGun.txt
 *    │       ├── PetrovGlider.txt
 *    │       ├── Simkin glider gun.txt
 *    │       ├── gunstar.txt
 *    │       └── lifePattern-Glider.txt
 *    ├── src
 *    │   ├── automata
 *    │   │   ├── Cell.cpp
 *    │   │   ├── Cell.hpp
 *    │   │   ├── Gen.cpp
 *    │   │   ├── Gen.hpp
 *    │   │   ├── pattern.cpp
 *    │   │   └── pattern.hpp
 *    │   ├── game
 *    │   │   ├── Controller.cpp
 *    │   │   ├── Controller.hpp
 *    │   │   ├── game_life.cpp
 *    │   │   ├── game_life.hpp
 *    │   │   └── main.cpp
 *    │   ├── math
 *    │   │   ├── Grid.cpp
 *    │   │   ├── Grid.hpp
 *    │   │   ├── Loc.cpp
 *    │   │   └── Loc.hpp
 *    │   └── utils
 *    │       ├── global.hpp
 *    │       ├── input.hpp
 *    │       ├── output.hpp
 *    │       └── parser.hpp
 *    └── tasks.py
 *
 * Special Features
 * - The grid is unbounded.
 * - The game can be resized at any time.
 * - Cells can be added by clicking on the grid.
 * - The board can be moved around.
 */

#include <iostream>
#include <unordered_set>
#include "parser.hpp"

using namespace std;

#include "input.hpp"
#include "output.hpp"

#include "Gen.hpp"
#include "game_life.hpp"

#include "pattern.hpp"

Gen init_state(int height, int width) {
    vector<string> choose = {
        "pattern from file",
        "random pattern"
    };

    int choice = input::select("How would you like to initialize the game?", choose);

    Gen initial_state;
    switch (choice) {
        case 1: {
            ifstream filename = input::get_input();
            vector<string> grid_lines = parser::consume_file(filename);
            initial_state = pattern::parse_gen(grid_lines);
        } break;
        case 2: {
            int percent_alive = input::integer("What percentage of cells should be alive?(0-100) ");
            initial_state = pattern::random_gen(height, width, percent_alive);
        } break;
    }

    return initial_state;
}


int main() {

    cout << "Welcome to Game of Life!" << endl;
    output::separate();

    do {
        Gen initial_state = init_state(20, 20);

        game_life::GameLife game(initial_state, 20, 20);
        game.run(cout);

        output::separate();
    } while (input::yes_or_no("Would you like to play again?"));
    return 0;
}
