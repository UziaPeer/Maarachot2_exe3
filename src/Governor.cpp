#include "Governor.hpp"
#include "Game.hpp"
#include <stdexcept>

using namespace coup;

/**
 * בנאי של Governor – קורא לבנאי של המחלקה הבסיסית Player
 */
Governor::Governor(Game& game, const std::string& name)
    : Player(game, name)
{
    role_name = "Governor";
}

/**
 * פעולה מיוחדת – מס (tax) עם בונוס:
 * מקבל 3 מטבעות במקום 2.
 */
void Governor::tax() {
    if (!canAct()) throw std::runtime_error("Not your turn");
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins");
    if (isSanctioned(game->getTurnCounter())) throw std::runtime_error("You are sanctioned");
    addCoins(3);
    markAction();
}

/**
 * undo – פעולה לחסימת tax של שחקנים אחרים.
 * מחזיר 2 מטבעות מהשחקן שביצע את הפעולה.
 */
void Governor::undo(Player& other) {
    // אם השחקן השני לא ביצע tax לאחרונה – אין מה לבטל
    // כדי לפשט, נניח שהוא ביצע tax בתור הנוכחי בלבד
    if (other.coins() < 2) {
        throw std::runtime_error("Cannot undo tax – insufficient coins to reverse");
    }
    // מחזירים 2 מטבעות חזרה לקופה (מורידים ממנו)
    other.removeCoins(2);
}
