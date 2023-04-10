#include "game.h"

Game::Game(int width, int height, std::vector<Player::Type> players_type):
    term_{true, false},
    field_{term_, width, height}/*,
    is_main_menu_open_{true},
    is_pause_menu_open_{false}*/ {
    
    term_.save_screen();
    std::cerr << cursor_off();
    std::cerr << clear_screen();

    for (auto player_type : players_type) {
        switch (player_type) {
        case Player::Type::computer:
            players_.push_back(new Computer(field_));
            break;
        case Player::Type::human:
            players_.push_back(new Human(term_, field_));
            break;
        default:
            std::cerr << "unexpected player_type\n";
            break;
        }
    }
    // std::cerr << "Game constructed\n";
}

Game::~Game() {
    for (auto player : players_) {
        delete player;
    }
    // std::cerr << "Game deconstructed\n";
    term_.restore_screen();
    std::cout << cursor_on();
}


void Game::Start() {
    // field_.field_[]
    field_.Render();

    bool game_is_on = true;

    // bool round_continues = true;

    for (auto player = players_.begin(); game_is_on;) { //loop for players
        if (player == players_.end()) {
            player = players_.begin();
        }

        try {
            Point cursor =  (*player)->GetCursor();
            switch ((*player)->GetForce()) {
            case Force::cross:
                field_.field_[cursor.x][cursor.y].cross_cursor = true;
                break;
            case Force::zero:
                field_.field_[cursor.x][cursor.y].zero_cursor = true;
                break;
            }
            
            field_.Render();
            (*player)->Move();
            
            if (field_.IsForceWin((*player)->GetForce())) {
                (*player)->IncrementScore();
                switch ((*player)->GetForce()) {
                case Force::cross :
                    std::cerr << "Cross win!\n";
                    break;
                case Force::zero :
                    std::cerr << "Zero win!\n";
                    break;
                default:
                    std::cerr << "Empty win! (error)\n";
                    break;
                }
                std::cerr << "Press Esc to exit\n";

                while (term_.read_key() != Key::ESC) {}
                throw Player::Exception::exit;
            }
            if (field_.IsDraw()) {
                std::cerr << "Draw!\n";
                std::cerr << "Press Esc to exit\n";
                while (term_.read_key() != Key::ESC) {}
                throw Player::Exception::exit;
            }
            ++player;
        }
        catch(const Player::Exception& e) {
            switch (e) {
            case Player::Exception::pause:
                std::cerr << "pause is under construction\n";
                break;
            case Player::Exception::exit:
                game_is_on = false;
                std::cerr << "Exit game\n";
                break;
            default:
                std::cerr << "Unexpected Player::Exception\n";
                break;
            }
        }
    }
}




/*
now: 
game construct
game start
    players make moves until draw or someone wins or esc pressed.
game deconstruct




future plans:
main menu:
    new game:
        loop of two players making moves:
            pause:
                resume
                main menu
            move
            is_win
            is_draw
        
    continue game:

    setings:
        width:      <15>
        height:     <15>
        player1:    <human/computer>
        player2:    <human/computer>
        theme:      <dark/light>
        set to default:
            confirm: yes/no


*/