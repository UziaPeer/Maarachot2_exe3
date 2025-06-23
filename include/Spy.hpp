// peeruzia@gmail.com
#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * מחלקת Spy (מרגל)
     * תכונות מיוחדות:
     * - יכול להסתכל על כמות המטבעות של שחקן אחר.
     * - יכול למנוע מהשחקן להשתמש ב־arrest בתור הבא שלו.
     * - הפעולה לא נחשבת לתור ולא עולה מטבעות.
     */
    class Spy : public Player {
    public:
        // בנאי
        Spy(Game& game, const std::string& name);

        // פעולה מיוחדת – "מעקב" אחרי שחקן אחר (חוסם לו arrest)
        void track(Player& other);
    };
}
