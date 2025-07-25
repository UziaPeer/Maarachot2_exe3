
Email: peeruzia@gmail.com  
Id: 318410263

# מטלה מספר 3 - מימוש משחק קו (Coup)

## תיאור כללי

במטלה אני מממש את משחק הקו (Coup) בשפת ++C.  
במשחק יש מספר תפקידים עם יכולות ייחודיות, ממשק לניהול תורות, חוקים שונים (כמו הפיכה, מעצר, שוחד וכו') והגדרות מחמירות של תנאים וחריגות לפי חוקי המשחק.

הקוד כתוב בצורה מודולרית ומבוסס על ירושה, וניהול זיכרון בטוח.  
לצורך ההדגמה נוספה גם המחשה טקסטואלית (`Demo.cpp`)

הקוד רץ בסביבת **(WSL) Linux** עם `make`.

---

## מבנה התיקיות

![image](https://github.com/user-attachments/assets/a235819d-7060-483e-8b12-fa5be4734c91)

---

## פונקציות עיקריות ובעלי תפקידים 

### Game
- `turn()` – מחזיר את שם השחקן שתורו לשחק כעת.
- `players()` – מחזיר רשימה של שמות השחקנים שעדיין פעילים.
- `winner()` – מחזיר את שם המנצח אם נותר שחקן יחיד, אחרת זורק חריגה.

### Player 
 פעולות בסיסיות לכל שחקן:

 - `gather()` – איסוף מטבע אחד.
 - `tax()` – קבלת שני מטבעות.
 - `bribe()` – תשלום 4 מטבעות לתור נוסף.
 - `arrest(Player& other)` – לקיחת מטבע משחקן אחר.
 - `sanction(Player& other)` – חסימת פעולות כלכליות של שחקן אחר.
 - `coup(Player& other)` – הדחת שחקן מהמשחק.
 - `coins()` – כמות המטבעות של השחקן.
 - `markAction()` – סמן ביצוע פעולה בתור.

 ### תפקידים ייחודיים

- **נציב (Governor)** - כאשר מבצע `tax` מקבל 3 מטבעות במקום 2. בנוסך יכול לבטל פעולת tax של שחקנים אחרים
- **מרגל (Spy)** - כאשר מבצע פעולת `track` על שחקן אחר מודפס על הלוח כמות המטבעות של אותו השחקן, בנוסף אותו השחקן לא יוכל לבצע `arrest` בתורו הקרוב
- **ברון (Baron)** - יכול לבצע פעולת `invest` בה הוא משלם 3 מטבעות ומקבל בתמורה 6. בנוסף אם מבצעים עליו סנקציות הוא אוטומטית מקבל באותו הרגע מטבע נוסף (הסנקציות לא מתבטלות)
- **גנרל (General)** - יכול לבצע פעולת `undo` בעלות של 5 מטבעות בה הוא מחזיר למשחק שחקן שהודח על ידי `coup`. בנוסף אם הוא מותקף ב`arrest` על ידי שחקן אחר הוא מקבל ממנו חזרה את המטבע שהרוויח
- **שופט (Judge)** - יכול לבצע פעולת `undo` על שחקן שביצע `bribe` ובכך לבטל לו את התור הכפול בסבב הקרוב. בנוסף שחקן שביצע עליו `sanction` משלם 4 מטבעות במקום 3
- **סוחר (Merchant)** - במידה ובתחילת התור יש לו 3 מטבעות הוא מקבל מטבע נוסף באופן אוטומטי. בנוסף אם מבצעים עליו `arrest` הוא משלם 2 מטבעות לקופה במקום אחד לשחקן אחר
- **ג'וקר (Joker)** - תוספת שלי לשם הדגמה של ירושה רגילה וירושה וירטואלית, המחלקה יורשת את Governor ו־Baron וכן את הפעולות המיוחדות שביכולתם לבצע. (היא מסומנת בערה ולא ניתנת להרצה במהלך המשחק, ניתן להפעילה)

 ### Demo

הקובץ `Demo` הוא קובץ ההדגמה הראשי של המשחק
המטרה שלו היא להדגים שימוש במחלקות שכתבתי (`Game`, `Player`, וכל התפקידים המיוחדים)  
ולהציג את מהלך המשחק בפועל – כולל פעולות, תורות, הדחות וניצחון.

- התפריטים מוצגים בקונסול.
- כל שחקן רואה את מצב המשחק בתורו ומקבל תפריט שמותאם אישית לתפקידו (פעולות מיוחדות שרק הוא יכול לבצע)
  הקובץ בנוי כך: 
- יצירת מופע של `Game`.
- יצירת שחקנים מסוגים שונים והוספתם למשחק.
- כניסה ללולאה שמציגה את מצב השמחק, בודקת תור מי לשחק, מציעה לו תפריט פעולות דינאמי מותאם לתפקיד, בודקת ניצחון. בנוסף מוודאת חריגות במידת הצורך.
- הדגמת של מצב מסויים במשחק:
- 
   ![image](https://github.com/user-attachments/assets/8b68bd98-fcc3-4c77-a76f-e2e0041349d9)



---

## מטרות המטלה


### ירושה וירטואלית וירושה רגילה:
בפרויקט עשיתי שימוש בירושה וירטואלית במחלקות בעלי התפקידים אשר יורשות את Player בצורה וירטואלית (virtual public Player).
מחלקת Joker יורשת את Governor ו־Baron יחד בירושה רגילה ולכן בזכות הירושה הוירטואלית נמנע מצב שבו בכל פעם שניצור Joker יווצרו לו שני מופעים של Player ויש מופע אחד בלבד של Player לכל שחקן Joker.


### כלל השלושה (Rule of Three)
בפרויקט זה מימשתי את כלל השלושה בתוך המחלקה `Player`:
- בנאי העתקה (`Player(const Player& other)`), מעתיק את כל השדות של השחקן (שם, תפקיד, מצב מטבעות, דגלים פנימיים).
- אופרטור השמה (`Player& operator=(const Player& other)`), שמעתיק את כל השדות במקרה של השמה בין שחקנים
- מפרק (`~Player()`).
- בפועל בגלל השימוש בפרויקט ב-`smart pointers` במקרה שלנו `std::shared_ptr`, אנחנו לא באמת צריכים מפרק מותאם אישית כי הם מנהלים את הזיכרון באופן אוטומטי. גם את בנאי ההעתקה ואת הופרטור ההשמה הוספתי בעיקר לצורך ההדגמה שאני מבין את משמעותם ואת השימוש בהם אך אין להם שימוש משמעותי בפרויקט (הם כן נבדקים בטסטים)




---

## הרצה וקימפול

- `make Main` – קימפול התכנית
- `./Main` – להריץ את הקובץ הראשי 
- `make test` – קימפול והרצת בדיקות היחידה.
- `make valgrind` – בדיקת נזילות זיכרון. לבדיקת הזיכרון צריך להפעיל את המשחק ולבצע בו מהלכים. בסוף ההרצה הדוח יתקבל.
- `make clean` – ניקוי קבצים זמניים.

---

## בדיקות

הבדיקות בוצעו עם `doctest` 
כוללות בדיקות על:
- כל הפעולות אותן יכול לבצע שחקן רגיל
- כל הפעולות המיוחדות שיכולים לבצע רק בעלי תפקידים מסויימים
- פעולות חוקיות ובלתי חוקיות וזריקת חריגות בהתאם
- בונוסים ייחודיים של כל תפקיד שמתבצעים אוטומטית
- מימוש נכון של מקרי קצה וחוקים כמו arrest כפול, חובה לבצע coup עם 10 מטבעות וכד'.
  

---

## זיכרון

נבדק עם `valgrind`. לא נמצאו דליפות זיכרון.
כמו שהזכרתי קודם לשם בדיקת הvalgrind יש להריץ את התכנית ולבצע בה פעולות. בסיום התכנית יופק הדוח

---

## ממשק גרפי

בפרויקט הוספתי ממשק גרפי בסיסי שמדמה GUI, המימוש נעשה בתוך קובץ Demo.cpp. הממשק מציג את מצב המשחק, שמות השחקנים והתפריט בהתאם לתור הנוכחי  והכול בסביבת הקונסול.
מאחר ואני משתמש בWSL לא הצלחתי להפעיל ממשקי ספריות GUI כמו QT ו-SFML ולכן נעזרתי בבינה מלאכותית לצורך בניית הממשק הגרפי שמדמה GUI (הממשק הוא MockGUI), עם זאת אדגיש שרוב העבודה בוצעה על ידי וגם זו שלא בוצעה על ידי עברה שינויים רבים על ידי, וגם חלקים שלא שיניתי דאגתי להבין לעומק.

---




