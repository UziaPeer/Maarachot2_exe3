// peeruzia@gmail.com
#pragma once
#include <string>

namespace coup {

    class Game; 

    class Player {
    protected:          // משתנים מוגנים כדי לאפשר גישה למחלקות יורשות
        std::string name;
        std::string role_name;
        int coin_count;
        Game* game;
        bool active;

        int lastBribeTurn;              // תור האחרון בו השחקן שיחד
        int lastArrestedTurn;           // תור האחרון בו השחקן נעצר
        int sanctionedUntil;            // תור עד אליו השחקן תחת סנקציות 
        int arrestBlockUntilTurnCounter; // תור עד אליו חסום מלבצע arrest
        int sanctionedUntilTurnCounter; // תור עד אליו השחקן חסום כלכלית (תחת סנקציות)



    public:
        // בנאי – מקבל הפניה למשחק ואת שם השחקן
        Player(Game& g, const std::string& name);
        // כלל השלושה:
        // בנאי העתקה 
        Player(const Player& other);
        // אופרטור השמה
        Player& operator=(const Player& other);
        // דסטרוקטור
        ~Player();


        // מחזירה את שם השחקן
        std::string getName() const;

        // מחזירה את שם התפקיד של השחקן
        // שימושי לזיהוי סוג השחקן במשחק
        virtual std::string role() const;

        // מחזירה את מספר המטבעות של השחקן
        // שימושי לבדיקה האם השחקן יכול לבצע פעולות שדורשות מטבעות
        int coins() const;

        // בודקת האם השחקן פעיל במשחק(לא הודח)
        bool isActive() const;

        // פעולה שמאפשרת לשחקן לאסוף מטבע
        // פעולה בסיסית שמוסיפה מטבע אחד לשחקן
        virtual void gather();

        // פעולה שמאפשרת לשחקן לבצע מס (tax)
        // פעולה שמוסיפה 2 מטבעות לשחקן למעט מקרה מיוחד של נציב  שמקבל 3
        virtual void tax();

        // פעולה שמאפשרת לשחקן לשחד (bribe)
        // פעולה שמסירה 4 מטבעות מהשחקן ומעניקה לו תור כפול בסיבוב הבא
        virtual void bribe();

        // פעולה שמסירה מטבע אחד מהשחקן השני ומוסיפה אותו לשחקן הנוכחי
        virtual void arrest(Player& other);

        // פעולה שמטילה סנקציה על שחקן אחר 
        // פעולה שמסירה מטבעות מהשחקן הנוכחי וחוסמת את השחקן השני מלבצע מס או איסוף
        virtual void sanction(Player& other);

        // פעולה שמאפשרת לשחקן לבצע הפיכה (coup)
        // פעולה שמסירה 7 מטבעות מהשחקן ומדיחה שחקן אחר מהמשחק
        virtual void coup(Player& other);

        // פעולה שמבטלת פעולה של שחקן אחר (undo)
        // פעולה שמיועדת לתפקידים מסוימים בלבד
        virtual void undo(Player& other);

        // מוסיפה מטבעות לשחקן
        // שימושי כאשר השחקן מבצע פעולות שמזכות אותו במטבעות
        void addCoins(int amount);

        // מסירה מטבעות מהשחקן
        // שימושי כאשר השחקן מבצע פעולות שדורשות תשלום מטבעות
        void removeCoins(int amount);

        // מסמנת את סיום הפעולה של השחקן ומקדמת את התור
        void markAction();

        // בודקת האם השחקן יכול לבצע פעולה בתור הנוכחי
        // שימושי למניעת פעולות לא חוקיות
        bool canAct() const;
        
        //פונקציות שנועדו למנוע ביצוע arrest על אותו שחקן פעמיים ברציפות
        int getLastArrestedTurn() const;
        void setLastArrestedTurn(int turn);

        int getLastBribeTurn() const; // מחזירה את התור האחרון בו בשחקן שיחד

        void reactivate(); // מחזירה את השחקן למשחק לאחר שהודח

        void setArrestBlockTurn(int turn);   //  הגדרת תור חסימה מפעולת arrest
        bool isArrestBlocked() const;          // האם מותר לו לבצע arrest כעת

        void setSanctionedUntilTurn(int turn); // מגדיר את התור עד אליו השחקן תחת סנקציות
        bool isSanctioned() const;             // האם השחקן תחת סנקציות כעת
        
        bool hasExtraTurnNextRound = false;
        bool isUsingExtraTurn = false;
        
        

        friend class Game;
    };
}
