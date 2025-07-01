// peeruzia@gmail.com
#include "Governor.hpp"
#include "Game.hpp"
#include <stdexcept>

using namespace coup;

/**
 * בנאי – מקבל הפניה למשחק ואת שם השחקן
 *  יוצר אובייקט מסוג נציב ומגדיר את שם התפקיד
 */
Governor::Governor(Game& game, const std::string& name)
    : Player(game, name)
{
    role_name = "Governor";
}

/**
 *  מקבל 3 מטבעות במקום 2 בפעולת tax.
 */
void Governor::tax() {
    // בדיקה אם זה תורו של המושל
    if (!canAct()) throw std::runtime_error("Not your turn");
    // בדיקה אם יש לו 10 מטבעות – חובה לבצע הפיכה
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins");
    // בדיקה אם המושל תחת סנקציה 
    if (isSanctioned()) throw std::runtime_error("You are under sanction and cannot gather");
    addCoins(3);
    markAction();
}

/**
 * ביטול פעולת מס של שחקנים אחרים.
 * מחזיר לקופה 2 מטבעות מהשחקן שביצע את הפעולה.
 * פעולה זו ניתנת לביצוע על שחקנים שביצעו tax בתור האחרון שלהם בלבד.
 */
void Governor::undo(Player& other) {
    // בדיקה אם זה תורו של המושל
    if (!canAct()) throw std::runtime_error("Not your turn");

    // בדיקה אם יש למושל 10 מטבעות – חובה לבצע הפיכה
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins");

    // בדיקה אם לשחקן השני יש מספיק מטבעות כדי להחזיר
    if (other.coins() < 2) {
        throw std::runtime_error("Cannot undo tax – not enough coins to return");
    }

    // הסרת 2 מטבעות מהשחקן השני
    other.removeCoins(2);

    // סיום התור של המושל
    markAction();
}
