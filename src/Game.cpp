// peeruzia@gmail.com
#include "Game.hpp"
#include "Player.hpp"
#include <stdexcept>

using namespace std;

namespace coup {

Game::Game() : current_index(0) {}

void Game::addPlayer(Player* player) {
    if (player_list.size() >= 6) {
        throw runtime_error("Cannot add more than 6 players.");
    }
    player_list.push_back(player);
}

string Game::turn() const {
    if (player_list.empty()) {
        throw runtime_error("No players in the game.");
    }
    return player_list.at(current_index)->getName();
}

vector<string> Game::players() const {
    vector<string> names;
    for (Player* p : player_list) {
        if (p->isActive()) {
            names.push_back(p->getName());
        }
    }
    return names;
}

string Game::winner() const {
    int alive_count = 0;
    string last_name;
    for (Player* p : player_list) {
        if (p->isActive()) {
            alive_count++;
            last_name = p->getName();
        }
    }
    if (alive_count == 1) {
        return last_name;
    }
    throw runtime_error("Game is still ongoing.");
}

void Game::nextTurn() {
    size_t start_index = current_index;

    do {
        current_index = (current_index + 1) % player_list.size();
        if (player_list[current_index]->isActive()) {
            // איפוס חסימת sanction
            removeSanction(player_list[current_index]->getName());

            // איפוס דגלי תור
            player_list[current_index]->resetTurnFlags();

            return;
        }
    } while (current_index != start_index);

    throw runtime_error("No active players remaining.");
}



void Game::removePlayer(Player* player) {
    (void)player;
    // אין צורך למחוק את השחקן מהרשימה, רק לסמן אותו כלא פעיל
    // פשוט מבטל את השחקן (המחיקה תתבצע בפועל ע"י isActive = false)
    // לא מסיר מהרשימה כדי לא לשבור את האינדקסים
}

void Game::addSanction(const std::string& name) {
    sanctioned_players.insert(name);
}

void Game::removeSanction(const std::string& name) {
    sanctioned_players.erase(name);
}

bool Game::isSanctioned(const std::string& name) const {
    return sanctioned_players.count(name) > 0;
}

}
