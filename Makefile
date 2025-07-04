# Email: peeruzia@gmail.com
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# קבצי מקור
SRC = src/Player.cpp src/Game.cpp src/Governor.cpp src/Spy.cpp src/Baron.cpp \
      src/General.cpp src/Judge.cpp src/Merchant.cpp src/Joker.cpp

# קובץ הדגמה (Demo)
MAIN = Demo.cpp

# קובץ בדיקות
TEST = test/test.cpp

# ברירת מחדל - קומפילציה של הדמו
all: Main

# קומפילציית הדמו
Main: $(MAIN) $(SRC)
	$(CXX) $(CXXFLAGS) -o Main $(MAIN) $(SRC)

# קומפילציית בדיקות
test: test_exec

test_exec: $(TEST) $(SRC)
	$(CXX) $(CXXFLAGS) -o test_exec $(TEST) $(SRC)
	./test_exec

# בדיקת זליגות זיכרון
valgrind: Main
	valgrind --leak-check=full ./Main

# ניקוי קבצים בינאריים בלבד
clean:
	rm -f Main test_exec MockGUI

.PHONY: all Main test test_exec valgrind clean

MockGUI: MockGUI.cpp $(SRC)
	$(CXX) $(CXXFLAGS) -o MockGUI MockGUI.cpp $(SRC)


