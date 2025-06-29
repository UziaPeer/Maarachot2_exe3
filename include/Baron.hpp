// peeruzia@gmail.com
#pragma once
#include "Player.hpp"

namespace coup {

    /**
     * מחלקת Baron (ברון)
     * תכונות מיוחדות:
     * - יכול להשקיע: משלם 3 מטבעות ומקבל 6 (רווח של 3).
     * - אם חטף sanction, מקבל מטבע אחד פיצוי (כלומר מפסיד רק 2).
     */
    class Baron : virtual public Player {
    public:
        // בנאי
        Baron(Game& game, const std::string& name);

        // פעולה מיוחדת: השקעה – invest
        void invest();

        // override ל־sanction – עם פיצוי
        void sanction(Player& other) override;
    };
}
