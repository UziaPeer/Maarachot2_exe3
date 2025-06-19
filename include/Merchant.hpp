// peeruzia@gmail.com
#pragma once
#include "Player.hpp"

namespace coup {

class Merchant : public Player {
public:
    Merchant(Game& game, const std::string& name);

    void tax() override;
    void beginTurnBonus();       // נקרא בתחילת תורו
    void onArrest();             // מטפל במעצר
    void gather() override;

};

}
