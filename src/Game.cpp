// peeruzia@gmail.com
#include "Game.hpp"
#include "Player.hpp"
#include <iostream>

using namespace coup;

// בנאי – מאתחל את המשתנים
Game::Game() : current_index(0), turn_counter(0), game_started(false) {}

/**
 * מוסיף שחקן חדש למשחק.
 * רק אם המשחק עדיין לא התחיל.
 */
void Game::addPlayer(Player* player) {
    if (game_started) {
        throw std::runtime_error("Cannot add players after the game has started");
    }
    if (players_list.size() >= 6) {
        throw std::runtime_error("Cannot add more than 6 players");
    }
    players_list.push_back(player);
}

/**
 * מחזירה את שמות השחקנים שעדיין במשחק (פעילים)
 */
std::vector<std::string> Game::players() const {
    std::vector<std::string> result;
    for (auto* p : players_list) {
        if (p->isActive()) {
            result.push_back(p->getName());
        }
    }
    return result;
}

/**
 * מחזירה את שם השחקן שתורו עכשיו
 */
std::string Game::turn() const {
    if (players_list.empty()) {
        throw std::runtime_error("No players in game");
    }
    return getCurrentPlayer()->getName();
}

/**
 * מחזירה את המנצח אם יש אחד בלבד.
 * אחרת זורקת חריגה.
 */
std::string Game::winner() const {
    int alive = 0;
    std::string winnerName = "";

    for (auto* p : players_list) {
        if (p->isActive()) {
            alive++;
            winnerName = p->getName();
        }
    }

    if (alive == 1) {
        return winnerName;
    } else {
        throw std::runtime_error("The game is still ongoing");
    }
}

/**
 * מחזירה את השחקן שתורו כעת (כולל דילוג על מודחים)
 */
Player* Game::getCurrentPlayer() const {
    int count = players_list.size();
    int idx = current_index % count;

    // אם השחקן לא פעיל – מדלגים עד שנמצא פעיל
    while (!players_list[idx]->isActive()) {
        idx = (idx + 1) % count;
    }
    return players_list[idx];
}

/**
 * מעבירה את התור לשחקן הבא הפעיל
 */
void Game::advanceTurn() {
    int count = players_list.size();
    if (count == 0) return;

    game_started = true;

    // עדכון תור קודם
    auto& curr = *players_list[current_index];

    // אם השחקן הנוכחי משתמש עכשיו בתור כפול — ניתן לו להישאר
    if (curr.isUsingExtraTurn) {
        curr.isUsingExtraTurn = false; // סיים את תורו השני
        return;
    }

    // מעבר לשחקן הבא
    do {
        current_index = (current_index + 1) % count;
    } while (!players_list[current_index]->isActive());

    auto& next = *players_list[current_index];

    // אם השחקן הגיע לתורו ויש לו בונוס — נפעיל אותו
    if (next.hasExtraTurnNextRound) {
        next.hasExtraTurnNextRound = false;
        next.isUsingExtraTurn = true;
    }

    turn_counter++;
}



/**
 * מסירה שחקן שהודח מהמשחק
 * פשוט מסמנים אותו כלא פעיל – לא מוחקים פיזית
 */
void Game::removePlayer(Player* player) {
    player->active = false;
}

/**
 * מחזירה את מספר התור הנוכחי (עבור חסימות וכו')
 */
int Game::getTurnCounter() const {
    return turn_counter;
}

/**
 * האם המשחק התחיל (כלומר בוצעה פעולה)
 */
bool Game::hasStarted() const {
    return game_started;
}
