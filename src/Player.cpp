// peeruzia@gmail.com
#include "Player.hpp"
#include "Game.hpp"
#include <stdexcept>

using namespace std;
namespace coup {

Player::Player(Game& game, const string& name) : name(name), game(game), coin_count(0), active(true) {
    game.addPlayer(this);
}

void Player::gather() {
    if (!active) throw runtime_error("Player is not active.");
    if (game.turn() != name) throw runtime_error("Not your turn.");
    coin_count++;
    game.nextTurn();
}

void Player::tax() {
    throw runtime_error("This role cannot perform tax.");
}



void Player::coup(Player& target) {
    if (!active) throw std::runtime_error("Player is not active.");
    if (game.turn() != name) throw std::runtime_error("Not your turn.");
    if (!target.isActive()) throw std::runtime_error("Target is already out.");
    if (coin_count < 7) throw std::runtime_error("Not enough coins to perform coup.");

    deductCoins(7);
    target.active = false;  // מדיח את השחקן
    game.nextTurn();
}


string Player::getName() const {
    return name;
}

int Player::coins() const {
    return coin_count;
}

bool Player::isActive() const {
    return active;
}

void Player::addCoins(int amount) {
    coin_count += amount;
}

void Player::deductCoins(int amount) {
    if (coin_count < amount) throw runtime_error("Not enough coins.");
    coin_count -= amount;
}

void Player::arrest(Player& target) {
    if (!active) throw std::runtime_error("Player is not active.");
    if (game.turn() != name) throw std::runtime_error("Not your turn.");
    if (!target.isActive()) throw std::runtime_error("Target is not active.");

    if (target.getName() == last_arrested_name) {
        throw std::runtime_error("Cannot arrest the same player twice in a row.");
    }

    if (target.coins() < 1) {
        throw std::runtime_error("Target does not have any coins.");
    }

    // תהליך המעצר:
    target.deductCoins(1);
    this->addCoins(1);

    // התנהגות מיוחדת לתפקידים מסוימים (דריסה):
    target.onArrest();

    // עדכון מעקב אחר העצור האחרון:
    last_arrested_name = target.getName();

    // סיום תור
    game.nextTurn();
}

void Player::onArrest() {
    // ברירת מחדל – לא עושה כלום
}

void Player::sanction(Player& target) {
    if (!active) throw std::runtime_error("Player is not active.");
    if (game.turn() != name) throw std::runtime_error("Not your turn.");
    if (!target.isActive()) throw std::runtime_error("Target is not active.");
    if (coin_count < 3) throw std::runtime_error("Not enough coins to perform sanction.");

    deductCoins(3);
    game.addSanction(target.getName());

    // התפקיד של target מגיב
    target.onSanction(*this);

    game.nextTurn();
}

void Player::onSanction(Player& attacker) {
    (void)attacker;

    // ברירת מחדל – לא עושה כלום
}

bool Player::isSanctioned() const {
    return game.isSanctioned(name);
}

void Player::bribe() {
    if (!active) throw std::runtime_error("Player is not active.");
    if (game.turn() != name) throw std::runtime_error("Not your turn.");
    if (coin_count < 4) throw std::runtime_error("Not enough coins to bribe.");
    if (bribed_this_turn) throw std::runtime_error("Already bribed this turn.");

    deductCoins(4);
    bribed_this_turn = true;
}

bool Player::hasBribed() const {
    return bribed_this_turn;
}

void Player::markAction() {
    if (!canAct()) {
        throw std::runtime_error("You already acted this turn.");
    }
    action_taken_this_turn = true;
    if (!bribed_this_turn) {
        game.nextTurn();
    }
}

bool Player::canAct() const {
    return !action_taken_this_turn || bribed_this_turn;
}

void Player::resetTurnFlags() {
    bribed_this_turn = false;
    action_taken_this_turn = false;
}

void Player::cancelBribe() {
    bribed_this_turn = false;
}


}
