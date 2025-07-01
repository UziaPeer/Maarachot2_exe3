// peeruzia@gmail.com
#pragma once

#include "Governor.hpp"
#include "Baron.hpp"

namespace coup {
/**
 * מחלקת Joker
 * תכונות מיוחדות:
 * - יורש את הפעולות של Governor ו-Baron.
 * - tax, undo, invest, sanction יורש:
 */
class Joker : public Governor, public Baron {
public:

     // בנאי – מקבל הפניה למשחק ואת שם השחקן
    Joker(Game& game, const std::string& name);

};

}
