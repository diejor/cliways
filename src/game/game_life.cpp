#include <chrono>
#include <ostream>
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
    Grid<Cell> simple_view(Gen state, int height, int width, Loc start_loc) {
        Grid<Cell> view(height, width);
        
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                Loc loc(row, col);

                if (state.is_alive(loc + start_loc)) {
                    Cell cell(loc, true);
                    view[loc] = cell;
                }
            }
        }

        return view;
    }

    void print_view(Grid<Cell> view) {
        for (int row = 0; row < view.height(); row++) {
            for (int col = 0; col < view.width(); col++) {
                Loc index(row, col);
                cout << (view[index].alive ? "O " : ". ");
            }
            cout << endl;
        }
    }

    GameLife::GameLife(Gen initial_state, int generations_per_second) {
        this->current_gen = 0;
        this->history[current_gen] = initial_state;
        this->generations_per_second = generations_per_second;
    }

    void GameLife::add_gen(Gen const& gen) {
        current_gen = (current_gen + 1) % REMEMBERED_GENS;
        history[current_gen] = gen;
    }

    void capture_mouse(vector<Loc>& mouse_clicks) {
        MEVENT event;
        if (getmouse(&event) == OK) {
            if (event.bstate & BUTTON1_CLICKED) {
                int cell_x = event.x / 2;  // Adjust according to your cell size
                int cell_y = event.y;
                mouse_clicks.push_back(Loc(cell_y, cell_x));
            }
        }
    }

    void GameLife::run() {
        initscr();             // Start ncurses mode
        cbreak();              // Line buffering disabled
        noecho();              // Don't echo while we do getch
        keypad(stdscr, TRUE);  // Get function keys
        nodelay(stdscr, TRUE); // Non-blocking getch
        curs_set(0);           // Hide the cursor
        
        // Enable mouse events
        mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
        printf("\033[?1003h\n"); // For xterm-compatible terminals
        
        Loc start_loc(0, 0);
        bool paused = false;
        int scale = 0;
        vector<Loc> mouse_clicks;
        
        while (true) {
            int ch;
            while ((ch = getch()) != ERR) {  // Process all available input
                switch (ch) {
                    case KEY_UP:
                        start_loc = start_loc + Loc(-1, 0);
                        break;
                    case KEY_DOWN:
                        start_loc = start_loc + Loc(1, 0);
                        break;
                    case KEY_LEFT:
                        start_loc = start_loc + Loc(0, -1);
                        break;
                    case KEY_RIGHT:
                        start_loc = start_loc + Loc(0, 1);
                        break;
                    case ' ':
                        paused = !paused;
                        break;
                    case '+':
                        scale += 5;
                        cout << "scale: " << scale << endl;
                        break;
                    case '-':
                        if (scale > 0)
                            scale -= 5;
                        break;
                    case KEY_MOUSE:
                        capture_mouse(mouse_clicks);
                        break;
                }
            }

            system("clear");
            
            if (!paused) {
                Gen next_gen = history[current_gen].next_gen();
                add_gen(next_gen);
            }

            while (!mouse_clicks.empty()) {
                Loc click = mouse_clicks.back();
                mouse_clicks.pop_back();
                Loc loc = click + start_loc;
                history[current_gen].toggle(loc);
            }

            Grid<Cell> view = simple_view(history[current_gen], 10+scale, 20+scale, start_loc);
            print_view(view);


            this_thread::sleep_for(chrono::milliseconds(1000 / generations_per_second));
        }
    }

}
