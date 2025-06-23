// peeruzia@gmail.com
#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * מחלקת Merchant (סוחר)
     * תכונות מיוחדות:
     * - אם מתחיל תור עם 3 מטבעות או יותר → מקבל עוד מטבע אחד חינם.
     * - אם נעצר → משלם 2 מטבעות לקופה במקום להעביר אחד לשחקן שעצר אותו.
     */
    class Merchant : public Player {
    public:
        // בנאי
        Merchant(Game& game, const std::string& name);

        // override ל־gather – מוסיף בונוס בתחילת תור
        void gather() override;

        // override ל־arrest – סופג arrest בצורה שונה
        void arrest(Player& other) override;
    };
}
