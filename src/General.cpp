// peeruzia@gmail.com
#include "General.hpp"
#include <stdexcept>

using namespace std;

namespace coup {

General::General(Game& game, const string& name) : Player(game, name) {}

void General::tax() {
    if (!active) throw runtime_error("General is not active.");
    if (game.turn() != name) throw runtime_error("Not your turn.");
    coin_count += 2;
    game.nextTurn();
}

void General::blockCoup(Player& attacker) {
    if (coin_count < 5) {
        throw runtime_error("General does not have 5 coins to block coup.");
    }
    coin_count -= 5;
    // ההנחה: הקופ כבר בוצע - אז רק מחזירים את הנזק
    attacker.deductCoins(7); // משלם על כלום
    // שים לב – זה מונע את ההדחה ידנית, אתה צריך לדאוג לא להעיף את המותקף
}

void General::onArrest() {
    coin_count += 1;
}

}
