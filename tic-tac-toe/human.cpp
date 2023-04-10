#include "human.h"

Human::Human(Terminal& term, Field& field, Force force, int score):
    Player{field, force, score},
    term_{term} {
    type_ = Type::human;
    // std::cerr << "Human constructed\n";
}

Human::~Human() {
    // std::cerr << "Human deconstructed\n";
}

//remake pause with try catch
void Human::Move() {
    while (true) {
        int key = term_.read_key();
        Point new_cursor = cursor_;
        switch (key) {
        case Key::ENTER:
            if (field_.Move(force_, cursor_)) {
                field_.Render();
                // std::cerr << "Human moved\n";
                return;
            }
            // std::cerr << "Human not moved\n";
            break;
        case Key::ARROW_LEFT:
            new_cursor.x--;
            new_cursor.x += field_.GetWidth();
            new_cursor.x %= field_.GetWidth();
            break;
        case Key::ARROW_RIGHT:
            new_cursor.x++;
            new_cursor.x %= field_.GetWidth();
            break;
        case Key::ARROW_UP:
            new_cursor.y--;
            new_cursor.y += field_.GetHeight();
            new_cursor.y %= field_.GetHeight();
            break;
        case Key::ARROW_DOWN:
            new_cursor.y++;
            new_cursor.y %= field_.GetHeight();
            break;
        case Key::ESC:
            throw Exception::exit;
            break;
        default:
            std::cerr << "unexpected key: " << key << "\n";
            break;
        }
        switch (force_) {
        case Force::cross:
            field_.field_[cursor_.x][cursor_.y].cross_cursor = false;
            field_.field_[new_cursor.x][new_cursor.y].cross_cursor = true;
            break;
        case Force::zero:
            field_.field_[cursor_.x][cursor_.y].zero_cursor = false;
            field_.field_[new_cursor.x][new_cursor.y].zero_cursor = true;
            break;
        }
        cursor_ = new_cursor;
        field_.Render();
    }
}