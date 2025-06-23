#include "Judge.hpp"
#include "Game.hpp"

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
 * בודק אם השוחד בוצע בתור הנוכחי, ואז מוריד ממנו 4 מטבעות.
 */
void Judge::undo(Player& other) {
    // אם השוחד בוצע בתור הנוכחי – ניתן לבטל
    if (other.getLastBribeTurn() == game->getTurnCounter()) {
        if (other.coins() < 4) {
            throw std::runtime_error("Cannot undo bribe – player has spent the coins");
        }
        other.removeCoins(4);
    } else {
        throw std::runtime_error("No bribe to undo");
    }
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
