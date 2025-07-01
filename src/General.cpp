// peeruzia@gmail.com
#include "General.hpp"
#include "Game.hpp"

using namespace coup;

/**
 * בנאי – מקבל הפניה למשחק ואת שם השחקן
 *  יוצר אובייקט מסוג גנרל ומגדיר את שם התפקיד
 */
General::General(Game& game, const std::string& name)
    : Player(game, name)
{
    role_name = "General";
}

/**
 * פעולה זו מאפשרת לגנרל להחזיר שחקן מודח למשחק על ידי תשלום של 5 מטבעות.
 * הפעולה לא חוסמת את ההדחה בזמן אמת אלא מתבצעת לאחר ההדחה.
 * אם שחקן המטרה עדיין פעיל, הפעולה תיכשל.
 */
void General::blockCoup(Player& target) {
    // בדיקה אם זה תורו של הגנרל
    if (!canAct()) {
        throw std::runtime_error("Not your turn");
    }
    // בדיקה אם יש לגנרל 10 מטבעות – חובה לבצע הפיכה
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins"); 
    // בדיקה אם יש לגנרל מספיק מטבעות כדי לחסום את ההדחה
    if (coins() < 5) {
        throw std::runtime_error("Not enough coins to block coup");
    }

    // בדיקה אם שחקן המטרה עדיין פעיל – לא ניתן לחסום את ההדחה
    if (target.isActive()) {
        throw std::runtime_error("Target is still active – cannot block coup");
    }

    // תשלום על הפעולה
    removeCoins(5);
    // החזרת שחקן מודח למשחק
    target.reactivate();
    // סיום התור של הגנרל
    markAction();
}

