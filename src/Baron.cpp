// peeruzia@gmail.com
#include "Baron.hpp"
#include "Game.hpp"

using namespace coup;

/**
 * בנאי – מקבל הפניה למשחק ואת שם השחקן
 *  יוצר אובייקט מסוג ברון ומגדיר את שם התפקיד
 */
Baron::Baron(Game& game, const std::string& name)
    : Player(game, name)
{
    role_name = "Baron";
}

/**
 * פעולה מיוחדת: invest – משקיע 3 מטבעות, מקבל 6
 * הפעולה דורשת תור רגיל
 */
void Baron::invest() {
    if (!canAct()) throw std::runtime_error("Not your turn");
    // מעל 10 מטבעות חייב לבצע הפיכה
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins");
    // צריך לפחות 3 מטבעות כדי להשקיע
    if (coins() < 3) {
        throw std::runtime_error("Not enough coins to invest");
    }

    removeCoins(3); // משלם 3
    addCoins(6);    // מרוויח 6
    markAction();   // מסיים תור
}

