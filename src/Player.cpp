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

void Player::coup(Player& other) {
    throw runtime_error("This role cannot perform coup.");
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
