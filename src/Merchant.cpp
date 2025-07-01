// peeruzia@gmail.com
#include "Merchant.hpp"
#include "Game.hpp"

using namespace coup;

/**
 * בנאי – מקבל הפניה למשחק ואת שם השחקן
 *  יוצר אובייקט מסוג סוחר ומגדיר את שם התפקיד
 *  הפעולות המיוחדות של הסוחר אינן פעולות אקטיביות
 *  ולכן אין להן פונקציה משל עצמן אלא פשוט מבוצעות אוטומטית במהלך המשחק במקומות אחרים בקוד
 */
Merchant::Merchant(Game& game, const std::string& name)
    : Player(game, name)
{
    role_name = "Merchant";
}

