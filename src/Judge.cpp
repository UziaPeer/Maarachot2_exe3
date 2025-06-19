// peeruzia@gmail.com
#include "Judge.hpp"
#include <stdexcept>

using namespace std;

namespace coup {

Judge::Judge(Game& game, const string& name) : Player(game, name) {}

void Judge::tax() {
    if (!active) throw runtime_error("Judge is not active.");
    if (game.turn() != name) throw runtime_error("Not your turn.");
    coin_count += 2;
    game.nextTurn();
}

void Judge::undoBribe(Player& target) {
    if (!target.isActive()) {
        throw runtime_error("Target is not active.");
    }

    if (target.coins() < 4) {
        throw runtime_error("Target does not have 4 coins to lose.");
    }

    target.deductCoins(4);  // הוא מאבד את המטבעות – השוחד מתבטל
}

void Judge::onSanction(Player& attacker) {
    attacker.deductCoins(1);  // מי שתקף אותו משלם לקופה עוד מטבע
}

void Judge::undo(Player& target) {
    throw std::runtime_error("Judge cannot undo tax.");
}


}
