// peeruzia@gmail.com
#include "Judge.hpp"
#include "Game.hpp"
#include <iostream>


using namespace coup;

/**
 * בנאי – מקבל הפניה למשחק ואת שם השחקן
 *  יוצר אובייקט מסוג שופט ומגדיר את שם התפקיד
 */
Judge::Judge(Game& game, const std::string& name)
    : Player(game, name)
{
    role_name = "Judge";
}

    // פעולה זו מבטלת שוחד שביצע שחקן אחר וצריכה להתבצע לפני שיגיע שוב תורו
 void Judge::undo(Player& other) {
    // בדיקה אם השחקן בכלל קיבל תור כפול כי ביצע שוחד בסיבוב האחרון
    if (other.hasExtraTurnNextRound) {  
        // אם כן, מבטל את השוחד
        other.hasExtraTurnNextRound = false;
        std::cout << "(Judge) Bribe undone: player will not get an extra turn next round.\n";
    } else {
        // אם לא, זורק חריגה
        throw std::runtime_error("No bribe to undo");
    }

    markAction(); // סיום התור של השופט
}




