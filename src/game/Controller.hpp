
#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <ncurses.h>

#include "Gen.hpp"
#include "Loc.hpp"

struct View {
    Loc start_loc;
    int height;
    int width;

    View();
    View(int height, int width);

    void scale(double scale_factor);
};

struct Controller {
    vector<Loc> mouse_clicks;
    bool paused;
    bool exit;
    int generations_per_second;
    View view;
    
    Controller(int height, int width);

    static void init_ncurses() {
        initscr();             // Start ncurses mode
        keypad(stdscr, TRUE);  // Get function keys
        noecho();              // Don't echo while we do getch
        cbreak();              // Don't wait for enter
        curs_set(0);           // Don't show the cursor
        nodelay(stdscr, TRUE);
        mousemask(ALL_MOUSE_EVENTS, NULL);
    }

    static void end_ncurses() {
        endwin();
    }

    void handle_input();
    void toggle_clicks(Gen& gen);

    void capture_mouse(vector<Loc>& mouse_clicks);
    void wait();
};

#endif  // !CONTROLS_HPP
