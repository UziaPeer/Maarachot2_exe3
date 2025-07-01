// peeruzia@gmail.com
#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * מחלקת Baron 
     * תכונות מיוחדות:
     * - יכול להשקיע: משלם 3 מטבעות ומקבל 6 (רווח של 3).
     * - אם הטילו עליו סנקציות מקבל בונוס של מטבע אחד מהקופה
     */
    class Baron : virtual public Player {
    public:
        //  // בנאי – מקבל הפניה למשחק ואת שם השחקן
        Baron(Game& game, const std::string& name);

        // פעולה מיוחדת: השקעה – מאפשר לברון לשלם 3 מטבעות ולקבל 6 מטבעות
        void invest();

    };
}
