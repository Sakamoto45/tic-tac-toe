#pragma once

#include "player.h"
#include "../cpp-terminal/terminal.h"

using Term::Key;
using Term::Terminal;

class Human : public Player {
private:
    Terminal& term_;
    /* data */
public:
    Human(Terminal& term, Field& field, Force force = Force::cross, int score = 0);
    ~Human();
    void Move();
};