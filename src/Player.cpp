// peeruzia@gmail.com
#include "Player.hpp"
#include "Game.hpp"
#include <stdexcept>
#include "Judge.hpp"
#include "General.hpp"
#include "Baron.hpp"
#include "Merchant.hpp"
#include <iostream>


using namespace coup;

Player::Player(Game& g, const std::string& name)
    : name(name), role_name("Player"), coin_count(0), game(&g),
      active(true), lastBribeTurn(-1), lastArrestedTurn(-1), sanctionedUntil(-1), arrestBlockUntilTurnCounter (-1)
        , sanctionedUntilTurnCounter(-1)
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
    if (!canAct()) {
        throw std::runtime_error("Not your turn");
    }
    if (coins() >= 10) {
        throw std::runtime_error("Must perform coup with 10 coins");
    }

    removeCoins(4);
    lastBribeTurn = game->getTurnCounter();

    // 🟢 סמן שבסיבוב הבא השחקן יקבל תור כפול
    hasExtraTurnNextRound = true;

    // סיום התור הנוכחי
    markAction();
}


void Player::arrest(Player& other) {
    if (!canAct()) throw std::runtime_error("Not your turn");
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins"); 
    if (isArrestBlocked()) {
        throw std::runtime_error("You are blocked from using arrest this turn");
    }
      
    if (other.getLastArrestedTurn() == game->getTurnCounter() - 1) {
        throw std::runtime_error("Can't arrest same player twice in a row");
    }
    other.removeCoins(1);
    addCoins(1);
    if (dynamic_cast<General*>(&other) != nullptr) {
        // התוקף (השחקן הזה) מאבד מטבע
        removeCoins(1);
        // הגנרל מקבל את המטבע
        other.addCoins(1);
    }
    if (dynamic_cast<Merchant*>(&other) != nullptr) {
        //  התוקף מאבד את המטבע שכביכול הרוויח
        removeCoins(1);
        // הסוחר מאבד עוד מטבע
        other.removeCoins(1);
    }
    other.setLastArrestedTurn(game->getTurnCounter());
    markAction();
}

void Player::sanction(Player& other) {
    if (!canAct()) throw std::runtime_error("Not your turn");
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins"); 
    int cost = 3;

    // 🛡️ אם מבצעים סנקציה על שופט – העלות גבוהה יותר
    if (dynamic_cast<Judge*>(&other) != nullptr) {
        cost = 4;
    }

    if (coins() < cost) {
        throw std::runtime_error("Not enough coins for sanction");
    }

    removeCoins(cost);


    // הסנקציה תסתיים רק לאחר שיגיע תורו ויתבצע
    int turnNow = game->getTurnCounter();
    int totalPlayers = game->players().size();
    other.setSanctionedUntilTurn(turnNow + totalPlayers);  // עד לסיום תורו הבא

    // בונוס לברון: מקבל מטבע אם הוטל עליו sanction
    if (dynamic_cast<Baron*>(&other) != nullptr) {
        other.addCoins(1);
        std::cout << "(Bonus) Baron received +1 coin after being sanctioned.\n";
    }

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
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins"); 
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



// ✅ פונקציות שנוספו:

int Player::getLastBribeTurn() const {
    return lastBribeTurn;
}

void Player::reactivate() {
    active = true;
}

void Player::setArrestBlockTurn(int turn) {
    arrestBlockUntilTurnCounter = turn;
}

bool Player::isArrestBlocked() const {
    return arrestBlockUntilTurnCounter > game->getTurnCounter();
}


void Player::setSanctionedUntilTurn(int turn) {
    sanctionedUntilTurnCounter = turn;
}

bool Player::isSanctioned() const {
    return sanctionedUntilTurnCounter > game->getTurnCounter();
}

// Copy constructor
Player::Player(const Player& other)
    : name(other.name),
      role_name(other.role_name),
      coin_count(other.coin_count),
      game(other.game),
      active(other.active),
      lastBribeTurn(other.lastBribeTurn),
      lastArrestedTurn(other.lastArrestedTurn),
      sanctionedUntil(other.sanctionedUntil),
      arrestBlockUntilTurnCounter(other.arrestBlockUntilTurnCounter),
      sanctionedUntilTurnCounter(other.sanctionedUntilTurnCounter)
{
    // כאן אין צורך להוסיף משהו כי אין ניהול זיכרון, אבל אפשר לשים הודעה להדגמה:
    // std::cout << "Player copy constructor called\n";
}

// Copy assignment operator
Player& Player::operator=(const Player& other) {
    if (this != &other) {
        name = other.name;
        role_name = other.role_name;
        coin_count = other.coin_count;
        game = other.game;
        active = other.active;
        lastBribeTurn = other.lastBribeTurn;
        lastArrestedTurn = other.lastArrestedTurn;
        sanctionedUntil = other.sanctionedUntil;
        arrestBlockUntilTurnCounter = other.arrestBlockUntilTurnCounter;
        sanctionedUntilTurnCounter = other.sanctionedUntilTurnCounter;
    }
    // std::cout << "Player copy assignment operator called\n";
    return *this;
}

// Destructor
Player::~Player() {
    // std::cout << "Player destructor called\n";
}
