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
    if (!canAct()) throw std::runtime_error("Not your turn");

    std::cout << other.getName() << " has " << other.coins() << " coins.\n";

    int currentTurn = game->getTurnCounter();
    int numPlayers = game->players().size();

    // נגדיר שהשחקן לא יכול לעשות arrest עד לסוף תורו הבא
    other.setArrestBlockTurn(currentTurn + numPlayers);

}



