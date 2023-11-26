#ifndef LOC_HPP
#define LOC_HPP

#include <vector>
#include <cstddef>

using namespace std;

class Loc {
    private:
        int row;
        int col;
    public:
        Loc();
        Loc(int row, int col);

        int get_row() const;
        int get_col() const;

        bool operator==(const Loc& other) const;
        Loc operator+(const Loc& other) const;
        Loc operator-(const Loc& other) const;

        vector<Loc> neighbors() const;
};

struct LocHash {
    size_t operator()(const Loc& loc) const;
};


#endif // !LOC_HPP
