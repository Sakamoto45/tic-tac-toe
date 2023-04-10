#include "field.h"

Field::Field(Terminal& term, int width, int height):
    term_{term},
    width_{width},
    height_{height},
    field_{(u_int)width_, std::vector<Cell>{(u_int)height_, Cell()}} {
    // std::cerr << "Field constructed\n";
}


Field::~Field() {
    // std::cerr << "Field deconstructed\n";
}

void Field::Render() {
    std::string buffer;
    buffer.reserve(16 * 1024);
    // buffer.append(clear())
    
    buffer.append(move_cursor(1, 1));

    for (int row = 0; row < height_; ++row) {
        for (int col = 0; col < width_; ++col) {
            Cell& cell = field_[col][row];
            
            cell.bg = Color(0, 0, 0);
            switch (cell.force) {
            case Force::cross:
                cell.fg = Color(255, 0, 0);
                break;
            case Force::zero:
                cell.fg = Color(0, 255, 0);
                break;
            case Force::empty:
                cell.fg = Color(255, 255, 255);
                break;
            }


            if (cell.zero_cursor) {
                cell.fg = cell.bg;
                cell.bg = Color(0, 255, 0);
            }
            if (cell.cross_cursor) {
                cell.fg = cell.bg;
                cell.bg = Color(255, 0, 0);
            }
            
            
        }
    }

    for (int row = 0; row < height_; ++row) {
        for (int col = 0; col < width_; ++col) {
            Cell cell = field_[col][row];
            
            // buffer.append(color24_bg(cell.bg.r, cell.bg.g, cell.bg.b));
            if (col == 0) {
                buffer.append("\033[1m");
            } else {
                Cell left_cell = field_[col-1][row];
                buffer.append(color24_bg(left_cell.bg.r, left_cell.bg.g, left_cell.bg.b));
            }
            buffer.append(color24_fg(cell.bg.r, cell.bg.g, cell.bg.b));
            buffer.append("▐");


            buffer.append("\033[1m");
            buffer.append(color24_fg(cell.fg.r, cell.fg.g, cell.fg.b));
            buffer.append(color24_bg(cell.bg.r, cell.bg.g, cell.bg.b));
            switch (cell.force) {
            case Force::cross:
                buffer.append("X");
                break;
            case Force::zero:
                buffer.append("O");
                break;
            case Force::empty:
                buffer.append("·");
                break;
            }
            buffer.append("\033[0m");
            // buffer.append(color(fg:: )
            // long long fg = ((i+j)%2 ? 0x303030 : 0x505050);
            // long long bg = ((i+j)%2 ? 0x505050 : 0x303030);
            // if (j == 0) {
            //     fg = 0x000000;
            // }
            // Print("▌", fg, bg);
            // cout << CSI << ((i+j) % 2 ? 7 : 0) << "m";
            // Print(XO[field[i][j]], kSymbolColors[field[i][j]], ((i+j)%2 ? 0x505050 : 0x303030));            
        }
        // term_.
        // Print("▌", ((i+width_)%2 ? 0x303030 : 0x505050), 0x000000);
        // Reset();

        
        buffer.append("\033[49m");
        Cell cell = field_[width_ - 1][row];
        buffer.append(color24_fg(cell.bg.r, cell.bg.g, cell.bg.b));
        buffer.append("▌");


        buffer.append("\n");
    }
    // buffer.append("\033[39m");

    buffer.append("\033[39m");
    buffer.append("\033[49m");

    std::cout << buffer << std::flush;
}

int Field::GetWidth() {
    return width_;
}

int Field::GetHeight() {
    return height_;
}

const std::vector<std::vector<Field::Cell>>& Field::GetField() const {
    return field_;
}


void Field::Clear() {
    for (auto col : field_) {
        for (auto cell : col) {
            cell.force = Force::empty;
        }
    }
}

bool Field::Move(Force force, Point& cell) {
    if (cell.x < 0 || cell.x >= width_ || cell.y < 0 || cell.y > height_) {
        return false;
    } 
    if (field_[cell.x][cell.y].force != Force::empty) {
        return false;
    }
    field_[cell.x][cell.y].force = force;
    return true;
}

bool Field::IsForceWin_(Force force, int d_row, int d_col) {
    int row_from = std::max(0, -d_row * (kLineLen - 1));
    int row_to = height_ + std::min(0, -d_row * (kLineLen - 1));
    for (int row = row_from; row < row_to; ++row) { //row of first cell in line
        int col_from = std::max(0, -d_col * (kLineLen - 1));
        int col_to = width_ + std::min(0, -d_col * (kLineLen - 1));
        for (int col = col_from; col < col_to; ++col) { //col of first cell in line
            bool full_line = true;
            for (int cell = 0; cell < kLineLen; ++cell) { //cell in line
                if (field_[col +  d_col * cell][row + d_row * cell].force != force) {
                    full_line = false;
                    break;
                }
            }
            if (full_line) {
                //somehow render line on field
                return true;
            }
        }
    }
    return false;
}


bool Field::IsForceWin(Force force) {
    // horizontal
    if (IsForceWin_(force, 0, 1)) return true;
    // vertical
    if (IsForceWin_(force, 1, 0)) return true;
    // diagonal
    if (IsForceWin_(force, 1, 1)) return true;
    // antidiagonal
    if (IsForceWin_(force, 1, -1)) return true;
    return false;
}

bool Field::IsDraw_(int d_row, int d_col) {
    int row_from = std::max(0, -d_row * (kLineLen - 1));
    int row_to = height_ + std::min(0, -d_row * (kLineLen - 1));
    for (int row = row_from; row < row_to; ++row) { //row of first cell in line
        int col_from = std::max(0, -d_col * (kLineLen - 1));
        int col_to = width_ + std::min(0, -d_col * (kLineLen - 1));
        for (int col = col_from; col < col_to; ++col) { //col of first cell in line
            bool can_cross_win = true;
            bool can_zero_win = true;
            for (int cell = 0; cell < kLineLen; ++cell) { //cell in line
                if (field_[col +  d_col * cell][row + d_row * cell].force == Force::cross) {
                    can_zero_win = false;
                }
                if (field_[col +  d_col * cell][row + d_row * cell].force == Force::zero) {
                    can_cross_win = false;
                }
            }
            if (can_zero_win || can_cross_win) {
                return false;
            }
        }
    }
    return true;
}

bool Field::IsDraw() {
        // horizontal
    if (!IsDraw_(0, 1)) return false;
    // vertical
    if (!IsDraw_(1, 0)) return false;
    // diagonal
    if (!IsDraw_(1, 1)) return false;
    // antidiagonal
    if (!IsDraw_(1, -1)) return false;
    return true;
}

