
#ifndef PATTERN_HPP
#define PATTERN_HPP

#include <string>
#include <vector>

#include "parser.hpp"
#include "Gen.hpp"

using namespace std;

namespace pattern {
    Gen parse_gen(vector<string> grid_lines);
    Gen random_gen(int height, int width, int percent_alive);
}

#endif // !PATTERN_HPP
