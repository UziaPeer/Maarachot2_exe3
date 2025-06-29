// peeruzia@gmail.com
#pragma once

#include "Governor.hpp"
#include "Baron.hpp"

namespace coup {

class Joker : public Governor, public Baron {
public:
    Joker(Game& game, const std::string& name);
    // ה־Joker לא צריך פונקציות ייחודיות —
    // הוא יורש את tax, undo, invest, sanction דרך Governor ו־Baron.
};

}
