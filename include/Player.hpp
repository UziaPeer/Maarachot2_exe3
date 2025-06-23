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
    virtual void coup(Player& other);

    std::string getName() const;
    int coins() const;
    bool isActive() const;

    void addCoins(int amount);
    void deductCoins(int amount);

    std::string last_arrested_name;
    virtual void arrest(Player& target);
    virtual void onArrest(); // תפקידים יכולים לדרוס
    
    virtual void sanction(Player& target);
    virtual void onSanction(Player& attacker); // תפקידים יכולים להגיב
    bool isSanctioned() const;

    bool bribed_this_turn = false;
    bool action_taken_this_turn = false;

    virtual void bribe();
    bool hasBribed() const;
    void resetTurnFlags();  // לקרוא בתחילת תור
    void markAction();      // לסמן שבוצעה פעולה
    bool canAct() const;    // מותר לפעול?
    void cancelBribe();     // עבור Judge::undoBribe


};

}
