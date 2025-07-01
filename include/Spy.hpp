// peeruzia@gmail.com
#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * מחלקת Spy (מרגל)
     * תכונות מיוחדות:
     * - יכול להסתכל על כמות המטבעות של שחקן אחר ולמנוע ממנו לבצע מעצר בתורו הקרוב
     * - הפעולה לא נחשבת לתור ולא עולה מטבעות.
     */
    class Spy : public Player {
    public:
         // בנאי – מקבל הפניה למשחק ואת שם השחקן
        Spy(Game& game, const std::string& name);

        // פעולה מיוחדת – מעקב אחר שחקן ומניעה ממנו לבצע מעצר בתורו הקרוב
        void track(Player& other);
    };
}
