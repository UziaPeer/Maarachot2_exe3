#include "Merchant.hpp"
#include "Game.hpp"

using namespace coup;

/**
 * בנאי – מגדיר שם תפקיד
 */
Merchant::Merchant(Game& game, const std::string& name)
    : Player(game, name)
{
    role_name = "Merchant";
}

/**
 * gather – אם יש לו לפחות 3 מטבעות בתחילת התור,
 * מקבל אחד נוסף במתנה לפני הפעולה.
 */
void Merchant::gather() {
    if (!canAct()) throw std::runtime_error("Not your turn");

    if (isSanctioned(game->getTurnCounter())) {
        throw std::runtime_error("You are sanctioned");
    }

    // בונוס: אם יש 3 מטבעות או יותר – מוסיפים 1
    if (coin_count >= 3) {
        addCoins(1);
    }

    // כרגיל: מקבל עוד 1 מהקופה
    addCoins(1);
    markAction();
}

/**
 * arrest – כשסוחר נעצר:
 * במקום לאבד מטבע לשחקן השני → משלם 2 לקופה (למערכת)
 */
void Merchant::arrest(Player& other) {
    if (!canAct()) throw std::runtime_error("Not your turn");

    if (other.getLastArrestedTurn() == game->getTurnCounter() - 1) {
        throw std::runtime_error("Can't arrest same player twice in a row");
    }

    // מורידים לו 2 מטבעות – לא נותנים לשחקן השני
    if (other.coins() < 2) {
        throw std::runtime_error("Merchant has insufficient coins to pay arrest penalty");
    }

    other.removeCoins(2); // הקופה מקבלת
    other.setLastArrestedTurn(game->getTurnCounter());
    markAction();
}
