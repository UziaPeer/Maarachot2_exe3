// peeruzia@gmail.com
#include "Player.hpp"
#include "Game.hpp"
#include <stdexcept>

using namespace coup;

Player::Player(Game& g, const std::string& name)
    : name(name), role_name("Player"), coin_count(0), game(&g),
      active(true), lastBribeTurn(-1), lastArrestedTurn(-1), sanctionedUntil(-1), blockedArrestUntilTurnCounter(-1), sanctionedUntilTurnCounter(-1)
{
    g.addPlayer(this);
}

std::string Player::getName() const {
    return name;
}

std::string Player::role() const {
    return role_name;
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

void Player::removeCoins(int amount) {
    if (coin_count < amount) {
        throw std::runtime_error("Not enough coins");
    }
    coin_count -= amount;
}

void Player::gather() {
    if (!canAct()) throw std::runtime_error("Not your turn");
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins");  
    if (isSanctioned()) throw std::runtime_error("You are under sanction and cannot gather");
    addCoins(1);
    markAction();
}

void Player::tax() {
    if (!canAct()) throw std::runtime_error("Not your turn");
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins"); 
    if (isSanctioned()) throw std::runtime_error("You are under sanction and cannot gather");
    addCoins(2);
    markAction();
}

void Player::bribe() {
    if (!canAct()) throw std::runtime_error("Not your turn");
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins"); 
    removeCoins(4);
    lastBribeTurn = game->getTurnCounter();
    markAction();
}

void Player::arrest(Player& other) {
    if (!canAct()) throw std::runtime_error("Not your turn");
    if (!canArrestNow()) {
        throw std::runtime_error("You are blocked from using arrest this turn");
    }    
    if (other.getLastArrestedTurn() == game->getTurnCounter() - 1) {
        throw std::runtime_error("Can't arrest same player twice in a row");
    }
    other.removeCoins(1);
    addCoins(1);
    other.setLastArrestedTurn(game->getTurnCounter());
    markAction();
}

void Player::sanction(Player& other) {
    if (!canAct()) throw std::runtime_error("Not your turn");
    if (coins() < 3) throw std::runtime_error("Not enough coins for sanction");

    removeCoins(3);

    // הסנקציה תסתיים רק לאחר שיגיע תורו ויתבצע
    int turnNow = game->getTurnCounter();
    int totalPlayers = game->players().size();
    other.setSanctionedUntilTurn(turnNow + totalPlayers);  // עד לסיום תורו הבא

    markAction();
}


void Player::coup(Player& other) {
    if (!canAct()) throw std::runtime_error("Not your turn");
    if (coins() < 7) throw std::runtime_error("Not enough coins to coup");
    removeCoins(7);
    other.active = false;
    game->removePlayer(&other);
    markAction();
}

void Player::undo(Player& other) {
    (void)other; // מסמן שהפרמטר לא בשימוש כדי למנוע אזהרה
    throw std::runtime_error("This role cannot undo actions");
}

void Player::markAction() {
    game->advanceTurn();
}

bool Player::canAct() const {
    return game->getCurrentPlayer() == this;
}

int Player::getLastArrestedTurn() const {
    return lastArrestedTurn;
}

void Player::setLastArrestedTurn(int turn) {
    lastArrestedTurn = turn;
}

void Player::setSanction(int until) {
    sanctionedUntil = until;
}

bool Player::isSanctioned(int currentTurn) const {
    return currentTurn < sanctionedUntil;
}

// ✅ פונקציות שנוספו:

int Player::getLastBribeTurn() const {
    return lastBribeTurn;
}

void Player::reactivate() {
    active = true;
}

void Player::setBlockedArrestUntil(int turn) {
    blockedArrestUntilTurnCounter = turn;
}

bool Player::canArrestNow() const {
    if (!game) return true; // אם אין משחק – אין חסימה
    return game->getTurnCounter() >= blockedArrestUntilTurnCounter;
}

void Player::setSanctionedUntilTurn(int turn) {
    sanctionedUntilTurnCounter = turn;
}

bool Player::isSanctioned() const {
    return sanctionedUntilTurnCounter > game->getTurnCounter();
}