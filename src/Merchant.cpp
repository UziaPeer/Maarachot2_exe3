// peeruzia@gmail.com
#include "Merchant.hpp"
#include <stdexcept>

using namespace std;

namespace coup {

Merchant::Merchant(Game& game, const string& name) : Player(game, name) {}

void Merchant::tax() {
    if (!active) throw runtime_error("Merchant is not active.");
    if (game.turn() != name) throw runtime_error("Not your turn.");

    beginTurnBonus();  // מוסיף בונוס לפני הפעולה
    coin_count += 2;
    game.nextTurn();
}

void Merchant::beginTurnBonus() {
    if (coin_count >= 3) {
        coin_count += 1;
    }
}

void Merchant::onArrest() {
    if (coin_count < 2) {
        throw runtime_error("Merchant has less than 2 coins for arrest penalty.");
    }
    coin_count -= 2;
    // הכסף הולך לקופה (לא לשחקן שעצר)
}

}
