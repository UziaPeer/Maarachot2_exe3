#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * מחלקת General (גנרל)
     * תכונות מיוחדות:
     * - יכול לשלם 5 מטבעות כדי לבטל פעולה של coup נגדו או נגד שחקן אחר.
     * - אם נעצר (arrest), מקבל חזרה את המטבע שנלקח ממנו.
     */
    class General : public Player {
    public:
        // בנאי
        General(Game& game, const std::string& name);

        // פעולה מיוחדת: חסימת coup נגד שחקן מסוים
        void blockCoup(Player& target);

        // override ל־arrest – מחזיר לעצמו את המטבע שנלקח ממנו
        void arrest(Player& other) override;
    };
}
