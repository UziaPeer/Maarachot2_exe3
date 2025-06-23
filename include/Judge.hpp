#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * מחלקת Judge (שופט)
     * תכונות מיוחדות:
     * - יכול לבטל פעולה של שוחד (bribe) של שחקן אחר → השחקן מפסיד 4 מטבעות.
     * - אם מקבל sanction, המטיל משלם מטבע נוסף לקופה.
     */
    class Judge : public Player {
    public:
        // בנאי
        Judge(Game& game, const std::string& name);

        // פעולה מיוחדת: ביטול שוחד (undo bribe)
        void undo(Player& other) override;

        // override ל־sanction – המטיל משלם מטבע נוסף
        void sanction(Player& other) override;
    };
}
