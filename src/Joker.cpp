// peeruzia@gmail.com
#include "Joker.hpp"


using namespace coup;

Joker::Joker(Game& game, const std::string& name)
    : Player(game, name), Governor(game, name), Baron(game, name)
{
    role_name = "Joker";
}
