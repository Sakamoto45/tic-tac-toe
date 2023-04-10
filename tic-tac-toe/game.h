#pragma once

#include <iostream>
#include <vector>
#include "../cpp-terminal/terminal.h"
#include "field.h"
#include "player.h"
#include "human.h"
#include "computer.h"

// using Term::Key;
using Term::cursor_off;
using Term::cursor_on;
using Term::cursor_position_report;
using Term::move_cursor;
using Term::clear_screen;
using Term::Terminal;
// using namespace std;

class Game {
private:
    Terminal term_;
    Field field_;
    std::vector<Player*> players_;
    
    // bool is_main_menu_open_;
    // bool is_pause_menu_open_;
    // void MainMenu();
    // void PauseMenu();

public:
    Game(int width = 15, int height = 15,
        std::vector<Player::Type> players_type = {Player::Type::human, Player::Type::computer});
    ~Game();
    // void Render();
    // void Init();
    void Start();
    // bool Refresh();
};
