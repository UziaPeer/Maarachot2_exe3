// peeruzia@gmail.com
#pragma once
#include "Player.hpp"
#include <unordered_map>

namespace coup {

class Spy : public Player {
private:
    std::unordered_map<std::string, bool> arrest_blocked;

public:
    Spy(Game& game, const std::string& name);

    int reveal(Player& target) const;     // לראות כמה מטבעות יש לו
    void block_arrest(Player& target);    // לחסום את ה-arrest שלו

    bool isArrestBlocked(const std::string& player_name) const;
    void clearBlock(const std::string& player_name); // לקרוא לזה בתחילת התור של השחקן ההוא
    void tax() override;

};

}
