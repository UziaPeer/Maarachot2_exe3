// peeruzia@gmail.com
#include "General.hpp"
#include "Game.hpp"

using namespace coup;

/**
 * בנאי – הגדרת שם התפקיד
 */
General::General(Game& game, const std::string& name)
    : Player(game, name)
{
    role_name = "General";
}

/**
 * פעולה מיוחדת: חוסם coup נגד שחקן אחר או נגד עצמו
 * עולה 5 מטבעות מהגנרל, ומונעת את ההדחה
 * **שימו לב**: בפועל הפעולה לא באמת חוסמת – צריך לקרוא לה לפני או אחרי ה־coup
 * במשחק שלנו לא תומכים ב־"intercept" אמיתי בזמן אמת.
 */
void General::blockCoup(Player& target) {
    if (!canAct()) {
        throw std::runtime_error("Not your turn");
    }

    if (coins() < 5) {
        throw std::runtime_error("Not enough coins to block coup");
    }

    if (target.isActive()) {
        throw std::runtime_error("Target is still active – cannot block coup");
    }

    removeCoins(5);        // תשלום על הפעולה
    target.reactivate();   // החזרת שחקן מודח למשחק
    markAction();          // סיום התור של הגנרל
}


/**
 * גנרל נעצר – מקבל את המטבע שנלקח ממנו חזרה
 */
void General::arrest(Player& other) {
    if (!canAct()) throw std::runtime_error("Not your turn");

    if (other.getLastArrestedTurn() == game->getTurnCounter() - 1)
    {
        throw std::runtime_error("Can't arrest same player twice in a row");
    }

    // מסיר מטבע מהשחקן השני
    other.removeCoins(1);
    addCoins(1); // המטבע של השחקן הזה (הגנרל) – מוחזר אליו אוטומטית

    // מחזיר לעצמו את המטבע – כלומר לא מפסיד באמת כלום
    addCoins(1);

    other.setLastArrestedTurn(game->getTurnCounter());
    markAction();
}
