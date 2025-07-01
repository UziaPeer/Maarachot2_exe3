// peeruzia@gmail.com
#include "Joker.hpp"


using namespace coup;

// בנאי של מחלקת Joker
// יוצר אובייקט מסוג Joker ומגדיר את שם התפקיד כ"Joker"
// מחלקת Joker יורשת גם מ-Governor וגם מ-Baron בנוסף ל-Player
Joker::Joker(Game& game, const std::string& name)
    : Player(game, name), Governor(game, name), Baron(game, name)
{
    role_name = "Joker"; // הגדרת שם התפקיד
}
