// peeruzia@gmail.com
#include "Baron.hpp"
#include <stdexcept>

using namespace std;

namespace coup {

Baron::Baron(Game& game, const string& name) : Player(game, name) {}

void Baron::tax() {
    if (!active) throw runtime_error("Baron is not active.");
    if (game.turn() != name) throw runtime_error("Not your turn.");
    coin_count += 2;
    game.nextTurn();
}

void Baron::invest() {
    if (!active) throw runtime_error("Baron is not active.");
    if (game.turn() != name) throw runtime_error("Not your turn.");
    if (coin_count < 3) throw runtime_error("Not enough coins to invest.");

    coin_count -= 3;
    coin_count += 6;
    game.nextTurn();
}

void Baron::onSanction(Player& attacker) {
    (void)attacker;
    coin_count += 1;
}


}
