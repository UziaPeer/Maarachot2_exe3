// peeruzia@gmail.com
#include "Spy.hpp"
#include <stdexcept>

using namespace std;

namespace coup {

Spy::Spy(Game& game, const string& name) : Player(game, name) {}

int Spy::reveal(Player& target) const {
    if (!target.isActive()) throw runtime_error("Target not active.");
    return target.coins();
}

void Spy::block_arrest(Player& target) {
    if (!target.isActive()) throw runtime_error("Target not active.");
    arrest_blocked[target.getName()] = true;
}

bool Spy::isArrestBlocked(const string& player_name) const {
    auto it = arrest_blocked.find(player_name);
    return it != arrest_blocked.end() && it->second;
}

void Spy::clearBlock(const string& player_name) {
    arrest_blocked.erase(player_name);
}

void Spy::tax() {
    if (!active) throw std::runtime_error("Spy is not active.");
    if (game.turn() != name) throw std::runtime_error("Not your turn.");
    coin_count += 2;
    game.nextTurn();
}

}
