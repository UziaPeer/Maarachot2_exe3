// peeruzia@gmail.com
#pragma once
#include <string>
#include <vector>
#include <stdexcept>

namespace coup {
    class Player; // הצהרה מוקדמת

    /**
     * מחלקת Game – מייצגת משחק יחיד.
     * מנהלת את כל השחקנים, סדר התורות, ומי נשאר חי.
     */
    class Game {
    private:
        std::vector<Player*> players_list; // רשימת שחקנים פעילים
        int current_index;                 // אינדקס של תור השחקן הנוכחי
        int turn_counter;                  // מונה תורים כולל (גם אם שחקן הודח)
        bool game_started;                 // האם כבר החלו לשחק

    public:
        // בנאי
        Game();

        // הוספת שחקן (נקרא מהבנאי של Player)
        void addPlayer(Player* player);

        // מחזירה את רשימת השמות של השחקנים שעדיין במשחק
        std::vector<std::string> players() const;

        // מחזירה את שם השחקן שתורו כעת
        std::string turn() const;

        // מחזירה את שם המנצח – אם נותר רק שחקן אחד
        std::string winner() const;

        // פנימי: החזרת השחקן הנוכחי
        Player* getCurrentPlayer() const;

        // פנימי: קידום תור (לא כולל שחקנים מודחים)
        void advanceTurn();

        // פנימי: הסרת שחקן שהודח
        void removePlayer(Player* player);

        // פנימי: מחזיר את מספר התור הנוכחי (עבור חסימות וכו')
        int getTurnCounter() const;

        // פנימי: האם המשחק כבר התחיל
        bool hasStarted() const;
    };
}
