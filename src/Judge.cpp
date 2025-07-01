// peeruzia@gmail.com
#include "Judge.hpp"
#include "Game.hpp"
#include <iostream>


using namespace coup;

/**
 * בנאי – מגדיר שם תפקיד
 */
Judge::Judge(Game& game, const std::string& name)
    : Player(game, name)
{
    role_name = "Judge";
}

/**
 * undo – מבטל bribe (שוחד) של שחקן אחר.
 */

 void Judge::undo(Player& other) {
    // בדיקה אם השחקן בכלל קיבל תור כפול מ־bribe
    if (other.hasExtraTurnNextRound) {
        other.hasExtraTurnNextRound = false;
        std::cout << "(Judge) Bribe undone: player will not get an extra turn next round.\n";
    } else {
        throw std::runtime_error("No bribe to undo");
    }

    markAction(); // סיום התור של השופט
}




