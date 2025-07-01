// peeruzia@gmail.com
#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * מחלקת Merchant
     * תכונות מיוחדות:
     * - אם מתחיל תור עם 3 מטבעות או יותר מקבל עוד מטבע אחד חינם.
     * - אם נעצר משלם 2 מטבעות לקופה במקום להעביר אחד לשחקן שעצר אותו.
     */
    class Merchant : public Player {
    public:
         // בנאי – מקבל הפניה למשחק ואת שם השחקן
        Merchant(Game& game, const std::string& name);

    };
}
