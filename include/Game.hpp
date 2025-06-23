// peeruzia@gmail.com
#pragma once
#include <vector>
#include <string>
#include <unordered_set>

namespace coup {

class Player;

class Game {
private:
    std::vector<Player*> player_list;
    size_t current_index;
    std::unordered_set<std::string> sanctioned_players;

public:
    Game();

    void addPlayer(Player* player);
    std::string turn() const;
    std::vector<std::string> players() const;
    std::string winner() const;
    void nextTurn();
    void removePlayer(Player* player);
    void addSanction(const std::string& name);
    void removeSanction(const std::string& name);
    bool isSanctioned(const std::string& name) const;
};


}
