// peeruzia@gmail.com
#include "Joker.hpp"


using namespace coup;

// בנאי של מחלקת Joker
// יוצר אובייקט מסוג ג'וקר ומגדיר את שם התפקיד
// המחלקה יורשת את הפעולות של Governor ו-Baron בנוסף לתכונות הבסיסיות של Player
Joker::Joker(Game& game, const std::string& name)
    : Player(game, name), Governor(game, name), Baron(game, name)
{
    role_name = "Joker"; // הגדרת שם התפקיד
}
