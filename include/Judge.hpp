// peeruzia@gmail.com
#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * מחלקת Judge
     * תכונות מיוחדות:
     * - יכול לבטל פעולת שוחש של שחקן אחר (undo bribe).
     * - אם שחקן אחר ביצע עליו סנקציות המטיל ישלם מטבע נוסף לקופה (4 במקום 3)
     */
    class Judge : public Player {
    public:
         // בנאי – מקבל הפניה למשחק ואת שם השחקן
        Judge(Game& game, const std::string& name);

        // פעולה מיוחדת: ביטול שוחד (undo bribe)
        void undo(Player& other) override;

    };
}
