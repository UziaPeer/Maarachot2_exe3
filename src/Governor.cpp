// peeruzia@gmail.com
#include "Governor.hpp"
#include "Player.hpp"
#include <stdexcept>

using namespace std;

namespace coup {

Governor::Governor(Game& game, const string& name) : Player(game, name) {}

void Governor::tax() {
    if (!active) throw runtime_error("Governor is not active.");
    if (game.turn() != name) throw runtime_error("Not your turn.");
    
    coin_count += 3;
    game.nextTurn();
}

void Governor::undo(Player& target) {
    if (!target.isActive()) throw runtime_error("Target is not active.");
    
    int targetCoins = target.coins();

    // אם הוא לקח 2 או 3, נוריד אותם
    if (targetCoins >= 3) {
        target.deductCoins(3);
    } else if (targetCoins >= 2) {
        target.deductCoins(2);
    } else {
        throw runtime_error("Cannot undo tax: target has too few coins.");
    }
}

}
