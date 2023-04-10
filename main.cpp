#include <iostream>
#include "tic-tac-toe/game.h"

// using namespace std;

int main(int argc, char* argv[]) {


    int width = 15;
    int height = 15;
    bool human_move_first = true;

    if (argc >= 3) {
        width = atoi(argv[1]);
        height = atoi(argv[2]);
    }
    if (argc >= 4) {
        human_move_first = atoi(argv[3]);
    }
    
    

    // while (width < 5 || width > 40) {
    //     std::cout << "Input width: ";
    //     std::cin >> width;
    // }
    // while (height < 5 || height > 40) {
    //     std::cout << "Input height: ";
    //     std::cin >> height;
    // }
    // bool human_move_first;
    // std::cout << "Player move first? [true(1)/false(0)] ";
    // std::cin >> human_move_first;
    

    try {

        Game game{width, height,
            (human_move_first ?
            (std::vector<Player::Type>{Player::Type::human, Player::Type::computer}) :
            (std::vector<Player::Type>{Player::Type::computer, Player::Type::human}))};

        // Game game{width, height,
        //     std::vector<Player::Type>{Player::Type::computer, Player::Type::human}};
        
        // game.Init();
        game.Start();
    } catch (const std::logic_error& re) {
        std::cerr << "Logic error: " << re.what() << std::endl;
        return 3;
    } catch (const std::runtime_error& re) {
        std::cerr << "Runtime error: " << re.what() << std::endl;
        return 2;
    } catch (...) {
        std::cerr << "Unknown error." << std::endl;
        return 1;
    }
    return 0;
}