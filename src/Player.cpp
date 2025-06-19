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

void Player::bribe() {
    throw runtime_error("This role cannot perform bribe.");
}

void Player::arrest(Player& other) {
    throw runtime_error("This role cannot perform arrest.");
}

void Player::sanction(Player& other) {
    throw runtime_error("This role cannot perform sanction.");
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

}
