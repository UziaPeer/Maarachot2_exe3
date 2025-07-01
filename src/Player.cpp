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

// בנאי: מאתחל אובייקט שחקן עם שם, תפקיד ומספר מטבעות התחלתי.
// מוסיף את השחקן למשחק.
Player::Player(Game& g, const std::string& name)
    : name(name), role_name("Player"), coin_count(0), game(&g),
      active(true), lastBribeTurn(-1), lastArrestedTurn(-1), sanctionedUntil(-1), arrestBlockUntilTurnCounter(-1),
      sanctionedUntilTurnCounter(-1) {
    g.addPlayer(this);
}

// מחזיר את שם השחקן.
std::string Player::getName() const {
    return name;
}

// מחזיר את התפקיד של השחקן.
std::string Player::role() const {
    return role_name;
}

// מחזיר את מספר המטבעות הנוכחי של השחקן.
int Player::coins() const {
    return coin_count;
}

// בודק אם השחקן פעיל במשחק.
bool Player::isActive() const {
    return active;
}

// מוסיף מספר מטבעות מסוים למספר המטבעות של השחקן.
void Player::addCoins(int amount) {
    coin_count += amount;
}

// מסיר מספר מטבעות מסוים ממספר המטבעות של השחקן.
// זורק חריגה אם לשחקן אין מספיק מטבעות.
void Player::removeCoins(int amount) {
    if (coin_count < amount) {
        throw std::runtime_error("Not enough coins");
    }
    coin_count -= amount;
}

// מאפשר לשחקן לאסוף מטבע אחד אם זה תורו והוא לא תחת סנקציה.
// זורק חריגות עבור תנאים לא חוקיים.
void Player::gather() {
    if (!canAct()) throw std::runtime_error("Not your turn");
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins");  
    if (isSanctioned()) throw std::runtime_error("You are under sanction and cannot gather");
    addCoins(1);
    markAction();
}

// מאפשר לשחקן לאסוף שני מטבעות אם זה תורו והוא לא תחת סנקציה.
// זורק חריגות עבור תנאים לא חוקיים.
void Player::tax() {
    if (!canAct()) throw std::runtime_error("Not your turn");
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins"); 
    if (isSanctioned()) throw std::runtime_error("You are under sanction and cannot gather");
    addCoins(2);
    markAction();
}

// מאפשר לשחקן לשחד, עולה 4 מטבעות ומעניק תור נוסף בסיבוב הבא.
// זורק חריגות עבור תנאים לא חוקיים.
void Player::bribe() {
    if (!canAct()) {
        throw std::runtime_error("Not your turn");
    }
    if (coins() >= 10) {
        throw std::runtime_error("Must perform coup with 10 coins");
    }

    removeCoins(4);
    lastBribeTurn = game->getTurnCounter();

    // מסמן שהשחקן יקבל תור נוסף בסיבוב הבא.
    hasExtraTurnNextRound = true;

    // מסיים את התור הנוכחי.
    markAction();
}

// מאפשר לשחקן לעצור שחקן אחר, מעביר מטבעות ומחיל עונשים בהתאם לתפקידים.
// זורק חריגות עבור תנאים לא חוקיים.
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
        // התוקף (השחקן הזה) מאבד מטבע.
        removeCoins(1);
        // הגנרל מקבל את המטבע.
        other.addCoins(1);
    }
        // אם השחקן הנענש הוא סוחר הוא מאבד 2 מטבעות לקופה במקום אחד לתוקף
    if (dynamic_cast<Merchant*>(&other) != nullptr) {
        // התוקף מאבד את המטבע שהוא כביכול הרוויח.
        removeCoins(1);
        // הסוחר מאבד מטבע נוסף.
        other.removeCoins(1);
    }
    other.setLastArrestedTurn(game->getTurnCounter());
    markAction();
}

// מאפשר לשחקן להטיל סנקציה על שחקן אחר, מחיל עונשים בהתאם לתפקידים.
// זורק חריגות עבור תנאים לא חוקיים.
void Player::sanction(Player& other) {
    if (!canAct()) throw std::runtime_error("Not your turn");
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins"); 
    int cost = 3;

    // אם מטילים סנקציה על שופט, העלות גבוהה יותר.
    if (dynamic_cast<Judge*>(&other) != nullptr) {
        cost = 4;
    }

    if (coins() < cost) {
        throw std::runtime_error("Not enough coins for sanction");
    }

    removeCoins(cost);

    // הסנקציה מסתיימת רק לאחר התור הבא של המטרה.
    int turnNow = game->getTurnCounter();
    int totalPlayers = game->players().size();
    other.setSanctionedUntilTurn(turnNow + totalPlayers);  // עד סוף התור הבא שלהם.

    // בונוס לברון: מקבל מטבע אם הוטלה עליו סנקציה.
    if (dynamic_cast<Baron*>(&other) != nullptr) {
        other.addCoins(1);
        std::cout << "(Bonus) Baron received +1 coin after being sanctioned.\n";
    }

    markAction();
}

// מאפשר לשחקן לבצע הפיכה, מסיר שחקן אחר מהמשחק.
// עולה 7 מטבעות וזורק חריגות עבור תנאים לא חוקיים.
void Player::coup(Player& other) {
    if (!canAct()) throw std::runtime_error("Not your turn");
    if (coins() < 7) throw std::runtime_error("Not enough coins to coup");
    removeCoins(7);
    other.active = false;
    game->removePlayer(&other);
    markAction();
}

// זורק חריגה מכיוון שתפקיד זה (שחקן כללי) לא יכול לבטל פעולות.
void Player::undo(Player& other) {
    if (coins() >= 10) throw std::runtime_error("Must perform coup with 10 coins"); 
    (void)other; // מסמן את הפרמטר כלא בשימוש כדי להימנע מאזהרות.
    throw std::runtime_error("This role cannot undo actions");
}

// מסמן את הפעולה של השחקן ומתקדם בתור המשחק.
void Player::markAction() {
    game->advanceTurn();
}

// בודק אם זה תורו של השחקן לפעול.
bool Player::canAct() const {
    return game->getCurrentPlayer() == this;
}

// מחזיר את התור האחרון שבו השחקן נעצר.
int Player::getLastArrestedTurn() const {
    return lastArrestedTurn;
}

// מגדיר את התור האחרון שבו השחקן נעצר.
void Player::setLastArrestedTurn(int turn) {
    lastArrestedTurn = turn;
}

// מחזיר את התור האחרון שבו השחקן שיחד.
int Player::getLastBribeTurn() const {
    return lastBribeTurn;
}

// מפעיל מחדש את השחקן במשחק.
void Player::reactivate() {
    active = true;
}

// מגדיר את התור עד אליו השחקן חסום מלעצור.
void Player::setArrestBlockTurn(int turn) {
    arrestBlockUntilTurnCounter = turn;
}

// בודק אם השחקן חסום מלעצור.
bool Player::isArrestBlocked() const {
    return arrestBlockUntilTurnCounter > game->getTurnCounter();
}

// מגדיר את התור עד אליו השחקן תחת סנקציה.
void Player::setSanctionedUntilTurn(int turn) {
    sanctionedUntilTurnCounter = turn;
}

// בודק אם השחקן כרגע תחת סנקציה.
bool Player::isSanctioned() const {
    return sanctionedUntilTurnCounter > game->getTurnCounter();
}

// בנאי העתקה: יוצר אובייקט שחקן חדש כהעתק של אחר.
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
      sanctionedUntilTurnCounter(other.sanctionedUntilTurnCounter) {
}

// אופרטור השמה העתקה: משייך את הערכים של אובייקט שחקן אחר לזה.
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
    return *this;
}

// דסטרוקטור: מנקה את אובייקט השחקן.
Player::~Player() {
    // אין צורך בניקוי מיוחד כי אין משאבים דינמיים
    // השחקן מוסר את עצמו מהמשחק בעת ההדחה
}
