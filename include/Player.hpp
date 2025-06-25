// peeruzia@gmail.com
#pragma once
#include <string>

namespace coup {

    class Game; // קדימה

    class Player {
    protected:
        std::string name;
        std::string role_name;
        int coin_count;
        Game* game;
        bool active;

        int lastBribeTurn;
        int lastArrestedTurn;
        int sanctionedUntil;
        int arrestBlockUntilTurnCounter; // תור עד אליו חסום לבצע arrest
        int sanctionedUntilTurnCounter; // תור עד אליו השחקן חסום כלכלית



    public:
        Player(Game& g, const std::string& name);
        virtual ~Player() = default;

        std::string getName() const;
        virtual std::string role() const;
        int coins() const;
        bool isActive() const;

        virtual void gather();
        virtual void tax();
        virtual void bribe();
        virtual void arrest(Player& other);
        virtual void sanction(Player& other);
        virtual void coup(Player& other);
        virtual void undo(Player& other);

        void addCoins(int amount);
        void removeCoins(int amount);

        void markAction();
        bool canAct() const;

        int getLastArrestedTurn() const;
        void setLastArrestedTurn(int turn);
        void setSanction(int until);
        bool isSanctioned(int currentTurn) const;

        // ✅ פונקציות שהוספנו:
        int getLastBribeTurn() const;
        void reactivate();

        void setArrestBlockTurn(int turn);   // הגדרת תור חסימה
        void setSanctionedUntilTurn(int turn); // קובע עד איזה תור תהיה חסימה
        bool isSanctioned() const;             // האם השחקן חסום כעת
        bool isArrestBlocked() const;        // האם כרגע חסום מ-arrest         // האם מותר לו לבצע arrest כעת

        friend class Game;
    };
}
