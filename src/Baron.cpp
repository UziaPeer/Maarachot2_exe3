#include "Baron.hpp"
#include "Game.hpp"

using namespace coup;

/**
 * בנאי של Baron – מגדיר את שם התפקיד
 */
Baron::Baron(Game& game, const std::string& name)
    : Player(game, name)
{
    role_name = "Baron";
}

/**
 * פעולה מיוחדת: invest – משקיע 3 מטבעות, מקבל 6
 * זוהי פעולה רגילה שדורשת להיות בתור.
 */
void Baron::invest() {
    if (!canAct()) throw std::runtime_error("Not your turn");

    // צריך לפחות 3 מטבעות כדי להשקיע
    if (coins() < 3) {
        throw std::runtime_error("Not enough coins to invest");
    }

    removeCoins(3); // משלם 3
    addCoins(6);    // מרוויח 6
    markAction();   // מסיים תור
}

/**
 * Baron מותקף ב־sanction → מקבל פיצוי של מטבע
 * כלומר משלם רק 2 במקום 3
 */
void Baron::sanction(Player& other) {
    if (!canAct()) throw std::runtime_error("Not your turn");

    if (coins() < 2) {
        throw std::runtime_error("Not enough coins to pay sanction (even reduced)");
    }

    removeCoins(2); // רק 2 מטבעות
    other.setSanction(game->getTurnCounter() + 1); // חוסם את הפעולות שלו
    markAction();
}
