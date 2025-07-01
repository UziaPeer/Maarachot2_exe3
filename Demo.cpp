// Email: peeruzia@gmail.com

#include "Game.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "Joker.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>

using namespace std;
using namespace coup;

// 🟢 פונקציה להדפסת מצב המשחק הנוכחי
void printGameState(const Game& game, const vector<shared_ptr<Player>>& players) {
    cout << "\n========== Game State ==========\n";
    for (const auto& p : players) {
        cout << p->getName()
             << " (" << p->role() << ")"
             << (p->isActive() ? " [Active]" : " [Eliminated]")
             << " - Coins: " << p->coins() << "\n";
    }
    cout << "================================\n";
    cout << "Current Turn: " << game.turn() << "\n";
}

// 🟢 פונקציה לבחירת שחקן יעד (חי בלבד)
int chooseTarget(const vector<shared_ptr<Player>>& players, const string& currentName) {
    cout << "\nChoose a target player by number:\n";
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i]->getName() != currentName && players[i]->isActive()) {
            cout << i << ". " << players[i]->getName() << "\n";
        }
    }
    int target = -1;
    cin >> target;
    if (target < 0 || target >= (int)players.size() || !players[target]->isActive()) {
        throw runtime_error("Invalid target player");
    }
    return target;
}

// 🟢 פונקציה לבחירת שחקן יעד מכל מצב (גם מודח)
int chooseAnyTarget(const vector<shared_ptr<Player>>& players) {
    cout << "\nChoose any target player by number:\n";
    for (size_t i = 0; i < players.size(); ++i) {
        cout << i << ". " << players[i]->getName();
        if (!players[i]->isActive()) cout << " (Eliminated)";
        cout << "\n";
    }
    int target = -1;
    cin >> target;
    if (target < 0 || target >= (int)players.size()) {
        throw runtime_error("Invalid target player");
    }
    return target;
}

// 🟢 פונקציה ראשית - הרצת המשחק בלולאה
int main() {
    Game game;

    // 🟢 יצירת שחקנים והוספה למשחק
    vector<shared_ptr<Player>> players = {
        make_shared<Governor>(game, "Alice"),
        make_shared<Spy>(game, "Bob"),
        make_shared<Baron>(game, "Charlie"),
        make_shared<Judge>(game, "Dana"),
        make_shared<General>(game, "Eyal"),
        make_shared<Merchant>(game, "Tamar"),
       // make_shared<Joker>(game, "JokerMan")
    };

    while (true) {
        try {
            printGameState(game, players);

            string currentName = game.turn();
            shared_ptr<Player> currentPlayer;

            // 🟢 איתור השחקן שבתורו
            for (auto& p : players) {
                if (p->getName() == currentName && p->isActive()) {
                    currentPlayer = p;
                    break;
                }
            }

            // 🟢 בונוס ל-Merchant אם יש לו 3+ מטבעות בתחילת התור
            if (auto merchant = dynamic_pointer_cast<Merchant>(currentPlayer)) {
                if (merchant->coins() >= 3) {
                    merchant->addCoins(1);
                    std::cout << "(Bonus) Merchant received +1 coin at start of turn.\n";
                    printGameState(game, players);
                 }
            }

            if (!currentPlayer) {
                cout << "No active player for this turn.\n";
                break;
            }

            // 🟢 תפריט פעולות
            cout << "\nTurn: " << currentPlayer->getName() << " (" << currentPlayer->role() << ")\n";
            cout << "Choose action:\n";
            cout << "1. gather\n2. tax\n3. bribe\n4. arrest\n5. sanction\n6. coup\n";

            if (dynamic_pointer_cast<Spy>(currentPlayer)) {
                cout << "7. track (Spy)\n";
            }
            if (dynamic_pointer_cast<Baron>(currentPlayer)) {
                cout << "8. invest (Baron)\n";
            }
            if (dynamic_pointer_cast<Governor>(currentPlayer)) {
                cout << "9. undo (Governor)\n";
            }
            if (dynamic_pointer_cast<General>(currentPlayer)) {
                cout << "10. block coup (General)\n";
            }
            if (dynamic_pointer_cast<Judge>(currentPlayer)) {
                cout << "11. undo bribe (Judge)\n";
            }
            if (dynamic_pointer_cast<Merchant>(currentPlayer)) {
                cout << "🟢 Merchant: If you have 3+ coins at start, you get +1 automatically with gather.\n";
            }

            cout << "0. Exit game\n";

            int action = -1;
            cin >> action;

            if (cin.fail()) {
                cin.clear(); // מנקה מצב שגיאה
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // מדלג על הקלט הבעייתי
                throw runtime_error("Invalid input - please enter a valid number from the menu");
            }

            if (action == 0) {
                cout << "Game ended.\n";
                break;
            }

            // 🟢 פעולות שדורשות בחירת יעד
            if (action == 4 || action == 5 || action == 6 ||
                action == 7 || action == 9 || action == 11) {
                int targetIndex = chooseTarget(players, currentPlayer->getName());
                auto& target = players[targetIndex];

                if (action == 4) currentPlayer->arrest(*target);
                else if (action == 5) currentPlayer->sanction(*target);
                else if (action == 6) currentPlayer->coup(*target);
                else if (action == 7) {
                    if (auto spy = dynamic_pointer_cast<Spy>(currentPlayer)) {
                        spy->track(*target);
                    }
                }
                else if (action == 9) {
                    if (auto gov = dynamic_pointer_cast<Governor>(currentPlayer)) {
                        gov->undo(*target);
                    }
                }
                else if (action == 11) {
                    if (auto judge = dynamic_pointer_cast<Judge>(currentPlayer)) {
                        judge->undo(*target);
                    }
                }
            } 
            // 🟢 פעולה של General לחסימת הפיכה
            else if (action == 10) {
                if (auto gen = dynamic_pointer_cast<General>(currentPlayer)) {
                    int idx = chooseAnyTarget(players);
                    gen->blockCoup(*players[idx]);
                }
            }            
            // 🟢 פעולות רגילות
            else {
                switch (action) {
                    case 1: currentPlayer->gather(); break;
                    case 2: currentPlayer->tax(); break;
                    case 3: currentPlayer->bribe(); break;
                    case 8: {
                        if (auto baron = dynamic_pointer_cast<Baron>(currentPlayer)) {
                            baron->invest();
                        }
                        break;
                    }
                    default: cout << "Invalid action\n";
                }
            }

            // 🟢 בדיקת ניצחון
            try {
                string win = game.winner();
                cout << "\n🏆 Winner: " << win << " 🏆\n";
                break;
            } catch (...) {
                // המשחק ממשיך
            }

        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}
