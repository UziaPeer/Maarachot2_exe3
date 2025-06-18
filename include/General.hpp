// peeruzia@gmail.com
#pragma once
#include "Player.hpp"

namespace coup {

class General : public Player {
public:
    General(Game& game, const std::string& name);

    void tax() override;
    void blockCoup(Player& attacker);     // חוסם הפיכה נגד מישהו
    void onArrest();                      // מקבל בחזרה את המטבע
};

}
