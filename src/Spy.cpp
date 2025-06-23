// peeruzia@gmail.com
#include "Spy.hpp"
#include "Game.hpp"
#include <iostream>

using namespace coup;

/**
 * בנאי של Spy – קורא לבנאי של Player ומגדיר את שם התפקיד
 */
Spy::Spy(Game& game, const std::string& name)
    : Player(game, name)
{
    role_name = "Spy";
}

/**
 * פעולה מיוחדת של Spy:
 * 1. מדפיס כמה מטבעות יש לשחקן השני.
 * 2. חוסם ממנו את פעולת arrest בתור הבא (לוגית, דרך תיעוד).
 *    כדי לשמר את הפשטות, נשתמש בשדה lastArrestedTurn שלו ונחסום דרכו.
 */
void Spy::track(Player& other) {
    // מציג את מספר המטבעות של השחקן הנעקב
    std::cout << other.getName() << " has " << other.coins() << " coins." << std::endl;

    // חוסם arrest בתור הבא: נשתמש בתרמית,
    // נשווה את lastArrestedTurn של השחקן הזה לתור הבא של השחקן האחר
    other.setLastArrestedTurn(game->getTurnCounter() + 1);
    
    // שים לב: לא משתמשים ב־markAction – כי זו פעולה חופשית שלא גובה תור!
}
