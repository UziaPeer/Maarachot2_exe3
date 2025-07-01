// peeruzia@gmail.com
#include "Merchant.hpp"
#include "Game.hpp"

using namespace coup;

/**
 * בנאי – מגדיר שם תפקיד
 */
Merchant::Merchant(Game& game, const std::string& name)
    : Player(game, name)
{
    role_name = "Merchant";
}

