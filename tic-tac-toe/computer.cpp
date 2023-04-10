#include "computer.h"

Computer::Computer(Field& field, Force force, int score):
    Player{field, force, score} {
    type_ = Type::computer;
    // std::cerr << "Computer constructed\n";
}

Computer::~Computer() {
    // std::cerr << "Computer deconstructed\n";
}
void Computer::Move_(Force opponent_force, int d_row, int d_col) {
    int height_ = field_.GetHeight();
    int width_ = field_.GetWidth();
    Force AI_force = force_;


    int row_from = std::max(0, -d_row * (kLineLen - 1));
    int row_to = height_ + std::min(0, -d_row * (kLineLen - 1));
    for (int row = row_from; row < row_to; ++row) { //row of first cell in line
        int col_from = std::max(0, -d_col * (kLineLen - 1));
        int col_to = width_ + std::min(0, -d_col * (kLineLen - 1));
        for (int col = col_from; col < col_to; ++col) { //col of first cell in line
            int opponent_value = 1;
            int AI_value = 2;
            for (int cell = 0; cell < kLineLen; ++cell) { //cell in line
                if (field_.field_[col +  d_col * cell][row + d_row * cell].force == AI_force) {
                    opponent_value *= 0;
                    AI_value *= 10;
                } else if (field_.field_[col +  d_col * cell][row + d_row * cell].force == opponent_force) {
                    opponent_value *= 10;
                    AI_value *= 0;
                }
            }
            
            for (int cell = 0; cell < kLineLen; ++cell) {
                if (field_.field_[col +  d_col * cell][row + d_row * cell].force == Force::empty) {
                    value[col +  d_col * cell][row + d_row * cell] += (opponent_value + AI_value);
                }
            }
        }
    }
}


void Computer::Move() {
    int height_ = field_.GetHeight();
    int width_ = field_.GetWidth();

    value = std::vector<std::vector<int>>((u_int)width_, std::vector<int>((u_int)height_, 0));


    Force opponent_force = (force_ == Force::cross ? Force::zero : Force::cross);


    // horizontal
    Move_(opponent_force, 0, 1);
    // vertical
    Move_(opponent_force, 1, 0);
    // diagonal
    Move_(opponent_force, 1, 1);
    // antidiagonal    
    Move_(opponent_force, 1, -1);

    
    Point best{width_ / 2, height_ / 2};
    for (int row = 0; row < height_; ++row) {
        for (int col = 0; col < width_; ++col) {
            if (value[col][row] > value[best.x][best.y]) {
                best.x = col;
                best.y = row;
            }
        }
    }
    switch (force_) {
    case Force::cross:
        field_.field_[cursor_.x][cursor_.y].cross_cursor = false;
        field_.field_[best.x][best.y].cross_cursor = true;
        break;
    case Force::zero:
        field_.field_[cursor_.x][cursor_.y].zero_cursor = false;
        field_.field_[best.x][best.y].zero_cursor = true;
        break;
    }
    cursor_ = best;
    field_.Move(force_, cursor_);
    field_.Render();
}