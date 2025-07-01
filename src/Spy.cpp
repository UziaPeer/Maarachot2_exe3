// peeruzia@gmail.com
#include "Spy.hpp"
#include "Game.hpp"
#include <iostream>

using namespace coup;

/**
 * בנאי – מקבל הפניה למשחק ואת שם השחקן
 *  יוצר אובייקט מסוג סוחר ומגדיר את שם התפקיד
 */
Spy::Spy(Game& game, const std::string& name)
    : Player(game, name)
{
    role_name = "Spy";
}

/**
 * פונקציה שמאפשרת למרגל לעקוב אחרי שחקן אחר ולבדוק כמה מטבעות יש לו,
 * בנוסף היא מונעת מאותו השחקן לעשות מעצר בתורו הקרוב
 */
void Spy::track(Player& other) {
    if (!canAct()) throw std::runtime_error("It's not your turn to play");
    if (coins() >= 10) throw std::runtime_error("You must perform a coup with 10 coins");
    std::cout << other.getName() << " has " << other.coins() << " coins.\n";

    int currentTurn = game->getTurnCounter();
    int numPlayers = game->players().size();

    // הגדרת חסימה לשחקן לבצע מעצר עד לסוף תורו הבא
    other.setArrestBlockTurn(currentTurn + numPlayers);

}



