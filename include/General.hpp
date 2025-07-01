// peeruzia@gmail.com
#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * מחלקת General 
     * תכונות מיוחדות:
     * - יכול לשלם 5 מטבעות ולבטל הפיכה על שחקן אחר
     * - אם שחקן אחר ביצע עליו מעצר הוא מקבל חזרה את המטבע שנלקח ממנו
     */
    class General : public Player {
    public:
         // בנאי – מקבל הפניה למשחק ואת שם השחקן
        General(Game& game, const std::string& name);

        // פעולת החסימה של ההפיכה במידה והשחקן שבוצעה עליו ההפיכה מודח
        void blockCoup(Player& target);

    };
}
