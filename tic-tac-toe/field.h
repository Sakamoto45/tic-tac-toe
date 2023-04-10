#pragma once

#include <iostream>
// #include <vector>
#include "../cpp-terminal/terminal.h"
// #include <math.h>


using Term::fg;
using Term::bg;
using Term::color;
using Term::color24_bg;
using Term::color24_fg;
using Term::move_cursor;
using Term::clear_screen;
// using Term::Key;
using Term::style;
using Term::Terminal;
// using namespace std;

const int kLineLen = 5;

enum class Force {
    empty,
    cross,
    zero
};

struct Point {
    int x;
    int y;
    Point(int x_, int y_):
        x{x_}, y{y_} {}

    // Point& operator+=(const Point& right) {
    //     x += right.x;
    //     y += right.y;
    //     return *this;
    // }
    //
    // Point operator*(const int& right) {
    //     Point res{x * right, y * right};
    //     return res;
    // }
};

struct Color {
    u_int r;
    u_int g;
    u_int b;
    Color(u_int r_, u_int g_, u_int b_):
        r{r_}, g{g_}, b{b_} {}
};

class Field {
private:
    Terminal& term_;
    int width_;
    int height_;
    
    

    struct Cell {
        Force force = Force::empty;
        Color fg{255, 255, 255};
        Color bg{0, 0, 0};
        // Color bg_left{0, 0, 0};
        bool cross_cursor = false;
        bool zero_cursor = false;
    };
    

    bool IsForceWin_(Force force, int d_row, int d_col); //assisting function for one direction check
    bool IsDraw_(int d_row, int d_col); //assisting function for one direction check
    // Line* Scan(bool (*func) (Line line));
    
public:
    
    std::vector<std::vector<Cell>> field_;
    Field(Terminal& term, int width, int height);
    ~Field();

    void Render();
    int GetWidth();
    int GetHeight();
    const std::vector<std::vector<Field::Cell>>& GetField() const;
    // Force GetCell(Point cell);
    void Clear();
    bool Move(Force force, Point& cell);
    bool IsForceWin(Force force);
    bool IsDraw();
    // fg Color;
    // bg 
};

// Line* Field::Scan(bool (*func) (const Line& line)) {
//     // Line
// }
