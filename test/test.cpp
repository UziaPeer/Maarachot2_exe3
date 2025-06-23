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

using namespace coup;

TEST_CASE("הוספה ובדיקה בסיסית של שחקנים") {
    Game g;

    Governor gov(g, "Alice");
    Spy spy(g, "Bob");
    CHECK(g.players().size() == 2);
    CHECK(g.turn() == "Alice");
}

TEST_CASE("בדיקת gather ו־tax") {
    Game g;
    Governor gov(g, "Alice");
    Spy spy(g, "Bob");

    CHECK_NOTHROW(gov.gather());         // Alice = 1
    CHECK_NOTHROW(spy.gather());         // Bob = 1
    CHECK(gov.coins() == 1);
    CHECK(spy.coins() == 1);

    CHECK_NOTHROW(gov.tax());            // Alice = 1+3=4
    CHECK(gov.coins() == 4);
}

TEST_CASE("חריגה כאשר שחקן פועל שלא בתורו") {
    Game g;
Governor gov(g, "Alice");
Spy spy(g, "Bob");

CHECK_THROWS(spy.gather());     // נסיון לגנוב תור – לפני ש-Alice שיחקה
CHECK_NOTHROW(gov.gather());    // Alice
CHECK_NOTHROW(spy.gather());    // Bob

}

TEST_CASE("פעולת undo של Governor") {
    Game g;
    Governor gov(g, "Alice");
    Spy spy(g, "Bob");

    gov.gather();     // 1
    spy.tax();        // 2

    CHECK(spy.coins() == 2);
    CHECK_NOTHROW(gov.undo(spy));
    CHECK(spy.coins() == 0); // הוריד ממנו 2
}

TEST_CASE("השקעה של Baron") {
    Game g;
    Baron b(g, "Baruch");
    Judge j(g, "Yarden");

    b.gather(); // 1
    j.gather(); // 1
    b.gather(); // 2
    j.gather(); // 2
    b.gather(); // 3
    j.gather(); // 3

    CHECK_NOTHROW(b.invest()); // עכשיו יש לו 6
    CHECK(b.coins() == 6);
}

TEST_CASE("בדיקת arrest כפול") {
    Game g;
    Spy s(g, "A");
    General gen(g, "B");

    s.gather(); // A
    gen.gather(); // B

    CHECK_NOTHROW(s.arrest(gen)); // מותר
    CHECK_THROWS(s.arrest(gen));  // פעמיים ברצף – אסור
}

TEST_CASE("שחקן עם 10 מטבעות חייב לבצע coup") {
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


