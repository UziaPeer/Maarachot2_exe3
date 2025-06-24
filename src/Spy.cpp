// peeruzia@gmail.com
#include "Spy.hpp"
#include "Game.hpp"
#include <iostream>

using namespace coup;

/**
 * בנאי של Spy – קורא לבנאי של Player ומגדיר את שם התפקיד
 */
Spy::Spy(Game& game, const std::string& name)
    : Player(game, name)
{
    role_name = "Spy";
}

void Spy::track(Player& other) {
    std::cout << other.getName() << " has " << other.coins() << " coins.\n";

    int turnNow = game->getTurnCounter();
    int totalPlayers = game->players().size();

    other.setBlockedArrestUntil(turnNow + totalPlayers); // חסימה עד סיום תורו הקרוב
}

