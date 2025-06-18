// peeruzia@gmail.com
#pragma once
#include "Player.hpp"

namespace coup {

class Baron : public Player {
public:
    Baron(Game& game, const std::string& name);

    void tax() override;       // כמו player רגיל
    void invest();             // הפעולה הייחודית
    void onSanction();         // קוראים לה אם נפגע מ-sanction
};

}
