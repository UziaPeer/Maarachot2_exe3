// peeruzia@gmail.com
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
 * פעולה זו נועדה להעניש שחקנים שביצעו tax בתור הנוכחי בלבד.
 */
void Governor::undo(Player& other) {
    // בדיקה אם זה תורו של המושל
    if (!canAct()) throw std::runtime_error("Not your turn");

    // בדיקה אם יש למושל 10 מטבעות – חובה לבצע הפיכה
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins");

    // בדיקה אם לשחקן השני יש מספיק מטבעות כדי להחזיר
    if (other.coins() < 2) {
        throw std::runtime_error("Cannot undo tax – insufficient coins to reverse");
    }

    // הסרת 2 מטבעות מהשחקן השני
    other.removeCoins(2);

    // סיום התור של המושל
    markAction();
}
