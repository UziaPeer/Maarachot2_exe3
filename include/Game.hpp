// peeruzia@gmail.com
#pragma once
#include <vector>
#include <string>

namespace coup {

class Player;

class Game {
private:
    std::vector<Player*> player_list;
    size_t current_index;

public:
    Game();

    void addPlayer(Player* player);
    std::string turn() const;
    std::vector<std::string> players() const;
    std::string winner() const;
    void nextTurn();
    void removePlayer(Player* player);
};

}
