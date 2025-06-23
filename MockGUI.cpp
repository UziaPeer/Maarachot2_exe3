// Email: peeruzia@gmail.com
#include "Game.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>

using namespace std;
using namespace coup;

void printGameState(const Game& game, const vector<shared_ptr<Player>>& players) {
    cout << "\n========== מצב המשחק ==========\n";
    for (const auto& p : players) {
        cout << p->getName()
             << " (" << p->role() << ")"
             << (p->isActive() ? " [פעיל]" : " [מודח]")
             << " - מטבעות: " << p->coins() << "\n";
    }
    cout << "================================\n";
    cout << "תור נוכחי: " << game.turn() << "\n";
}

int chooseTarget(const vector<shared_ptr<Player>>& players, const string& currentName) {
    cout << "\nבחר שחקן יעד לפי מספר:\n";
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i]->getName() != currentName && players[i]->isActive()) {
            cout << i << ". " << players[i]->getName() << "\n";
        }
    }
    int target = -1;
    cin >> target;
    if (target < 0 || target >= (int)players.size() || !players[target]->isActive()) {
        throw runtime_error("שחקן לא חוקי");
    }
    return target;
}

int main() {
    Game game;

    // יצירת שחקנים
    vector<shared_ptr<Player>> players = {
        make_shared<Governor>(game, "Alice"),
        make_shared<Spy>(game, "Bob"),
        make_shared<Baron>(game, "Charlie"),
        make_shared<Judge>(game, "Dana")
    };

    while (true) {
        try {
            printGameState(game, players);

            string currentName = game.turn();
            shared_ptr<Player> currentPlayer;

            for (auto& p : players) {
                if (p->getName() == currentName && p->isActive()) {
                    currentPlayer = p;
                    break;
                }
            }

            if (!currentPlayer) {
                cout << "אין שחקן פעיל בתור.\n";
                break;
            }

            cout << "\nתור של " << currentPlayer->getName() << " (" << currentPlayer->role() << ")\n";
            cout << "בחר פעולה:\n";
            cout << "1. gather\n";
            cout << "2. tax\n";
            cout << "3. bribe\n";
            cout << "4. arrest (דורש יעד)\n";
            cout << "5. sanction (דורש יעד)\n";
            cout << "6. coup (דורש יעד)\n";
            cout << "0. יציאה מהמשחק\n";

            int action = -1;
            cin >> action;

            if (action == 0) {
                cout << "המשחק הסתיים.\n";
                break;
            }

            if (action >= 4 && action <= 6) {
                int targetIndex = chooseTarget(players, currentPlayer->getName());
                auto& target = players[targetIndex];

                if (action == 4) currentPlayer->arrest(*target);
                else if (action == 5) currentPlayer->sanction(*target);
                else if (action == 6) currentPlayer->coup(*target);
            } else {
                switch (action) {
                    case 1: currentPlayer->gather(); break;
                    case 2: currentPlayer->tax(); break;
                    case 3: currentPlayer->bribe(); break;
                    default: cout << "פעולה לא מוכרת\n";
                }
            }

            // בדיקת מנצח
            try {
                string win = game.winner();
                cout << "\n🏆 המנצח הוא: " << win << " 🏆\n";
                break;
            } catch (...) {
                // המשחק עדיין ממשיך
            }

        } catch (const exception& e) {
            cout << "שגיאה: " << e.what() << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}
