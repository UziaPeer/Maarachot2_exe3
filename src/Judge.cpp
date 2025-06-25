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



/**
 * Judge סופג sanction – המטיל משלם מטבע נוסף
 */
void Judge::sanction(Player& other) {
    if (!canAct()) throw std::runtime_error("Not your turn");

    if (coins() < 3) {
        throw std::runtime_error("Not enough coins for sanction");
    }

    removeCoins(3); // השופט משלם רגיל

    if (other.coins() < 1) {
        throw std::runtime_error("Sanctioning Judge costs +1 – but player has no extra coin");
    }

    other.removeCoins(1); // השחקן שהטיל את החרם משלם עוד מטבע לקופה
    setSanction(game->getTurnCounter() + 1); // השופט נחסם עד סוף סיבוב הבא
    markAction();
}
