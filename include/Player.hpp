// peeruzia@gmail.com
#pragma once
#include <string>
#include "Game.hpp"

namespace coup {

class Player {
protected:
    std::string name;
    Game& game;
    int coin_count;
    bool active;

public:
    Player(Game& game, const std::string& name);
    virtual ~Player() = default;

    virtual void gather();     // פעולה בסיסית
    virtual void tax();        // ניתן לדרוס בתפקידים
    virtual void bribe();
    virtual void arrest(Player& other);
    virtual void sanction(Player& other);
    virtual void coup(Player& other);

    std::string getName() const;
    int coins() const;
    bool isActive() const;

    void addCoins(int amount);
    void deductCoins(int amount);
};

}
