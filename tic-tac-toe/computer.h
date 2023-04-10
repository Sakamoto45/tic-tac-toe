#pragma once

#include "player.h"

class Computer : public Player {
private:
    /* data */
    void Move_(Force opponent_force, int d_row, int d_col);
    std::vector<std::vector<int>> value;

    
public:
    Computer(Field& field, Force force = Force::zero, int score = 0);
    ~Computer();
    void Move();
};