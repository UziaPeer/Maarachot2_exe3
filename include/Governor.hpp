// peeruzia@gmail.com
#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * מחלקת Governor
     * תכונות מיוחדות:
     * - מקבל 3 מטבעות במקום 2 בפעולת tax
     * - יכול לבטל פעולת tax של שחקנים אחרים
     */
    class Governor : virtual public Player {
    public:
        // בנאי – מקבל הפניה למשחק ואת שם השחקן
        Governor(Game& game, const std::string& name);

        // פעולה מיוחדת – מס מחוזק (3 מטבעות)
        void tax() override;

        // פעולת חסימת הtax של שחקנים אחרים
        void undo(Player& other) override;
    };
}
