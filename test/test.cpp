// peeruzia@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Game.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "Joker.hpp"

using namespace coup;

// בדיקת gather - שחקן מתחיל עם 0 מטבעות, מבצע פעולה ומקבל מטבע אחד
TEST_CASE("gather basic") {
    Game game;
    Player p(game, "P1");
    CHECK(p.coins() == 0);
    p.gather();
    CHECK(p.coins() == 1);
}

// בדיקת tax - שחקן רגיל מקבל 2 מטבעות, מושל מקבל בונוס של מטבע נוסף
TEST_CASE("tax basic and Governor bonus") {
    Game game;
    Player p(game, "P1");
    Governor gov(game, "Gov1");

    p.tax();
    CHECK(p.coins() == 2);

    gov.tax();
    CHECK(gov.coins() == 3);
}

// בדיקת שוחד - עלות השוחד ותור נוסף לשחקן
TEST_CASE("bribe - cost and extra turn") {
    Game game;
    Player p(game, "P1");
    Player p2(game, "P2");
    p.addCoins(5);
    p.bribe();
    CHECK(p.hasExtraTurnNextRound == true);
    p2.gather(); 
    p.gather(); 
    CHECK(game.turn() == "P1");
    CHECK(p.coins() == 2);
}

// בדיקת arrest - אין אפשרות לבצע פעמיים ברצף על אותו השחקן, גנרל מקבל מטבע כפיצוי
TEST_CASE("arrest rules + General bonus") {
    Game game;
    Player p1(game, "P1");
    Player p2(game, "P2");
    General gen(game, "G1");

    p1.tax();
    p2.tax();
    gen.tax();

    p1.arrest(gen);

    CHECK(p1.coins() == 2);   
    CHECK(gen.coins() == 2);  // הגנרל קיבל בחזרה
   
    // arrest פעמיים ברצף - צריך לזרוק שגיאה
    CHECK_THROWS(p2.arrest(gen));
}


// בדיקת sanction - עלות הפעולה, פיצוי לברון ועלות גבוהה יותר לשופט
TEST_CASE("sanction rules") {
    Game game;
    Player p1(game, "P1");
    Player p2(game, "P2");
    Judge judge(game, "Judge1");
    Baron baron(game, "Baron1");

    p1.addCoins(9);
    p2.addCoins(9);
    // רגיל
    p1.sanction(baron);
    CHECK(p1.coins() == 6);
    CHECK(baron.coins() == 1); // קיבל פיצוי

    // על שופט - עלות 4
    p2.sanction(judge);
    CHECK(p2.coins() == 5);

    CHECK_THROWS(judge.gather());
}

// בדיקת coup - שחקן מדיח שחקן אחר, מאבד 7 מטבעות, השחקן המודח יוצא מהמשחק
TEST_CASE("coup rules") {
    Game game;
    Player p1(game, "P1");
    Player p2(game, "P2");
    p1.addCoins(7);

    p1.coup(p2);
    CHECK(p1.coins() == 0);
    CHECK(p2.isActive() == false);
}

// גנרל מחזיר שחקן שהודח חזרה למשחק ובדיקת העלות של הפעולה
TEST_CASE("General block coup") {
    Game game;
    Player p1(game, "P1");
    General gen(game, "Gen1");
    Player p2(game, "P2");

    p1.addCoins(7);
    p1.coup(p2);

    CHECK(p1.coins() == 0);
    CHECK(p2.isActive() == false);

    gen.addCoins(5);
    gen.blockCoup(p2);

    CHECK(gen.coins() == 0);
    CHECK(p2.isActive() == true);
}

// בדיקת track - בדיקה שהשחקן שבוצע עליו המעקב לא יכול לבצע מעצר בתורו
TEST_CASE("Spy track") {
    Game game;
    Spy spy(game, "Spy");
    Player target(game, "T");
    target.addCoins(5);

    spy.track(target);
    CHECK_THROWS(target.arrest(spy));
    //לא מצאתי דרך לבדוק שאכן הודפס מספר המטבעות של שחקן המטרה אך אפשר לוודא ע"י הרצת המשחק
}

// invest - הברון משקיע ומקבל מטבעות נוספים
TEST_CASE("Baron invest") {
    Game g;
    Baron b(g, "Baruch");
    Judge j(g, "Yarden");

    b.gather(); // 1
    j.gather(); // 1
    b.gather(); // 2
    j.gather(); // 2
    b.gather(); // 3
    j.gather(); // 3

    b.invest(); // עכשיו יש לו 6
    CHECK(b.coins() == 6);
}

// undo - governor מבטל את פעולת tax של שחקן אחר
TEST_CASE("governor undo") {
    Game g;
    Governor gov(g, "Alice");
    Spy spy(g, "Bob");

    gov.gather();     // 1
    spy.tax();        // 2

    CHECK(spy.coins() == 2);
    CHECK_NOTHROW(gov.undo(spy));
    CHECK(spy.coins() == 0); // הוריד ממנו 2
}

// undo - שופט מבטל שוחד של שחקן אחר
TEST_CASE("undo bribe") {
    Game game;
    Player p(game, "P1");
    Judge judge(game, "judge");
    p.addCoins(5);
    p.bribe();
    CHECK(p.hasExtraTurnNextRound == true);
    judge.undo(p); // מבטל את השוחד
    CHECK(p.hasExtraTurnNextRound == false); //מתבטל דגל השוחד
    p.gather(); //מבצע תור אחד
    CHECK(game.turn() == "judge"); //התור חזר לשופט
    CHECK(p.coins() == 2); //המטבעות לא חוזרים
}


/*
 מכיוון  שהבדיקה האם תור הסוחר כעת מתבצעת בתוך הלולאה של הרצת המשחק בקובץ דמו
ואינה חלק מהמחלקה של הסוחר, הבדיקה יכולה להתבצע ידנית בעת הרצת המשחק
TEST_CASE("Merchant bonus") {
    Game game;
    Merchant m(game, "M");
    Player p(game, "P1");
    m.tax(); // m = 2
    p.tax(); // p = 2
    m.tax(); // m = 4
    p.tax(); // p = 4
    m.tax(); // m = 7 = 4 + 2 + 1 (בונוס)
    CHECK(m.coins() == 7);
    p.tax(); // p = 6
    CHECK(p.coins() == 6);
}*/

// בדיקת חריגה כאשר שחקן פועל שלא בתורו
TEST_CASE("Exception when player acts out of turn") {
    Game g;
Governor gov(g, "Alice");
Spy spy(g, "Bob");

CHECK_THROWS(spy.gather());     // נסיון לגנוב תור – לפני ש-Alice שיחקה
CHECK_NOTHROW(gov.gather());    // Alice
CHECK_NOTHROW(spy.gather());    // Bob

}


// חובה לבצע הפיכה כאשר יש לשחקן 10 מטבעות או יותר בתחילת התור
TEST_CASE("Player with 10 coins must coup") {
    Game g;
    Governor gov(g, "Alice");
    Spy spy(g, "Bob");
    Baron baron(g, "Charlie");

    // gov עולה ל־9
    gov.tax();      // 3
    spy.gather();
    baron.gather();

    gov.tax();      // 6
    spy.gather();
    baron.gather();

    gov.tax();      // 9
    spy.gather();
    baron.gather();

    // תורו שוב
    CHECK(g.turn() == "Alice");

    // מוסיפים לו ידנית 1 (בלי לסיים תור)
    gov.addCoins(1);
    CHECK(gov.coins() == 10);

    // פעולה רגילה – אמורה להיכשל
    CHECK_THROWS(gov.tax());

    // coup – מותרת
    CHECK_NOTHROW(gov.coup(baron));
}

// בדיקה שהירושה של הג'וקר יורשת  פעולות מהברון ומהנציב
TEST_CASE("Joker מבצע invest ו־undo בלי להשתמש ב-tax") {
    Game g;
    Joker j(g, "JokerMan");
    Spy spy(g, "SpyGuy");

    // מעלה את הג׳וקר ל־3 מטבעות כדי שיוכל להשקיע
    j.gather();  // 1
    spy.gather(); // תור שלו — חובה לשמור על תורות
    j.gather();  // 2
    spy.gather();
    j.gather();  // 3
    spy.gather();

    CHECK(j.coins() == 3);

    // מבצע invest → יש לו 6 יותר, מינוס 3 ששילם → 6 בסוף
    CHECK_NOTHROW(j.invest());
    CHECK(j.coins() == 6);

    // עכשיו ה-Spy עושה tax
    spy.tax();
    CHECK(spy.coins() == 5);

    // Joker משתמש ב-undo (היכולת שלו כ-Governor) על ה-Spy — מבטל tax
    CHECK_NOTHROW(j.undo(spy));
    CHECK(spy.coins() == 3);
}

// בדיקת כלל השלושה - בנאי העתקה
TEST_CASE("Rule of three - Copy constructor") {
    Game g;
    Player p1(g, "Original");
    Player p2 = p1; // Copy constructor
    CHECK(p2.getName() == "Original");
}

// בדיקת כלל השלושה - אופרטור השמה
TEST_CASE("Rule of three - Copy assignment") {
    Game g;
    Player p1(g, "Original");
    Player p2(g, "Temp");
    p2 = p1; // Copy assignment
    CHECK(p2.getName() == "Original");
}

// בדיקת turn, players, winner - תור, שחקנים פעילים ומנצח
TEST_CASE("turn, players, winner") {
    Game game;
    Governor gov(game, "Gov");
    Spy spy(game, "Spy");

    // תור ראשון אמור להיות של Gov
    CHECK(game.turn() == "Gov");

    // בהתחלה יש 2 שחקנים פעילים
    CHECK(game.players().size() == 2);

    // בודקים שהשמות נכונים
    std::vector<std::string> activePlayers = game.players();
    CHECK(activePlayers[0] == "Gov");
    CHECK(activePlayers[1] == "Spy");

    // Gov מדיח את Spy
    gov.addCoins(7);
    gov.coup(spy);

    
    // רק Gov נשאר
    CHECK(game.players().size() == 1);
    activePlayers = game.players();
    CHECK(activePlayers[0] == "Gov");

    // בודקים האם ניצח
    CHECK(game.winner() == "Gov");
}



