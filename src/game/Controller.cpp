

#include <ncurses.h>

#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>
#include <vector>

#include "Controller.hpp"

using namespace std;

View::View(int height, int width) :
    height(height),
    width(width),
    start_loc(Loc(0, 0)) {
}

void View::scale(double scale_factor) {
    this->height *= scale_factor;
    this->width *= scale_factor;
}

Controller::Controller(int height, int width) :
    paused(true),
    exit(false),
    generations_per_second(3),
    view(View(height, width)) {
}

void Controller::handle_input() {
    int ch;
    while ((ch = getch()) != ERR) {
        switch (ch) {
            case KEY_UP:
                view.start_loc += Loc(-1, 0);
                break;
            case KEY_DOWN:
                view.start_loc += Loc(1, 0);
                break;
            case KEY_LEFT:
                view.start_loc += Loc(0, -1);
                break;
            case KEY_RIGHT:
                view.start_loc += Loc(0, 1);
                break;
            case ' ':
                paused = !paused;
                break;
            case '=':
                view.scale(1.5);
                break;
            case '-':
                view.scale(1.0 / 1.5);
                break;
            case 'u':
                generations_per_second++;
                break;
            case 'd':
                if (generations_per_second > 1) {
                    generations_per_second--;
                }
                break;
            case KEY_MOUSE:
                capture_mouse(mouse_clicks);
                break;
            case 'q':
                exit = true;
                end_ncurses();
                break;
            default:
                break;
        }

    }
}

void Controller::capture_mouse(vector<Loc>& mouse_clicks) {
    MEVENT event;
    if (getmouse(&event) == OK) {
        if (BUTTON1_CLICKED & event.bstate) {
            int row = event.y;
            int col = event.x / 2;
            mouse_clicks.push_back(Loc(row, col));
        }
    }
}

void Controller::toggle_clicks(Gen& gen) {
    for (Loc loc : mouse_clicks) {
        gen.toggle(loc + view.start_loc);
    }
    mouse_clicks.clear();
}

void Controller::wait() {
    this_thread::sleep_for(chrono::milliseconds(1000 / generations_per_second));
}

