#ifndef LOC_HPP
#define LOC_HPP

#include <vector>
#include <cstddef>

using namespace std;

class Loc {
    private:
        const int x;
        const int y;
    public:
        Loc();
        Loc(int x, int y);

        int row() const;
        int col() const;

        bool operator==(const Loc& other) const;
        Loc operator+(const Loc& other) const;
        Loc operator-(const Loc& other) const;

        vector<Loc> neighbors() const;
};

struct LocHash {
    size_t operator()(const Loc& loc) const;
};


#endif // !LOC_HPP
