// peeruzia@gmail.com
#pragma once
#include "Player.hpp"

namespace coup {

class Judge : public Player {
public:
    Judge(Game& game, const std::string& name);

    void tax() override;
    void undoBribe(Player& target);   // ביטול שוחד
    void onSanction(Player& attacker); // מעניש את זה שהפעיל עליו sanction
    void undo(Player& target);  // ← נזרוק שגיאה כמו בדמו

};

}
