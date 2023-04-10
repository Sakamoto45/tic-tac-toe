#include "player.h"

Player::Player(Field& field, Force force, int score):
    field_{field},
    force_{force},
    score_{score},
    cursor_{field_.GetWidth() / 2, field_.GetHeight() /2} {
    // std::cerr << "Player constructed\n";
}

Player::~Player() {
    // std::cerr << "Player deconstructed\n";

}

void Player::Move() {
}

int Player::GetScore() {
    return score_;
}

void Player::ResetScore() {
    score_ = 0;
}

void Player::IncrementScore() {
    ++score_;
}

Force Player::GetForce() {
    return force_;
}

Point Player::GetCursor() {
    return cursor_;
}