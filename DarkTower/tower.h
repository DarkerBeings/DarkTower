#include <iostream>
#include <windows.h>

using namespace std;

/* Colors
1: Blue
2: Green
3: Cyan
4: Red
5: Purple
6: Yellow (Dark)
7: Default white
8: Gray/Grey
9: Bright blue
10: Bright green
11: Bright cyan
12: Bright red
13: Pink/Magenta
14: Yellow
15: Bright white
*/
void SetColor(int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}

string line = "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

class Player { 
public:
    int warrior;
    int gold;
    int food;
    int pegasus;
    bool beast;
    bool scout;
    bool healer;
    bool sword; 
    int frontier;
    
    Player() {
        warrior = 10;
        gold = 30;
        food = 25;
        pegasus = 0;
        beast = 0;
        scout = false;
        healer = false;
        sword = false;
        frontier = 0;
    }
    Player (int war, int gold, int food, int peg, int beast, bool scout, bool healer, bool sword) {
        warrior = war;
        this->gold = gold;
        this->food = food;
        pegasus = peg;
        this->beast = beast;
        this->scout = scout;
        this->healer = healer;
        this->sword = sword;
        frontier = 0;
    }
    ~Player() {};
    
    void printInventory() {
        SetColor(6);
        std::cout << warrior << " Warriors, " << gold << " Gold, " << food << " Food.\n" <<
            scout << " Scout, " << healer << " Healer, " << beast << " Beast(s), " << pegasus << " Pegasus, "<<  sword << " Sword." << endl;
        SetColor(7);
    }
    /*
        Input amount of gold to add to players party.
        Each warrior a player has is repsonible for 6 bags of gold. 
        A beast will carry 50 bags of gold.
        If the added gold is more than the total capacity of gold, you lose the excess.gold
    */
    void updateGold(int add) {
        this->gold += add;
        this->gold = min(this->gold, this->warrior * 6 + (this->beast * 50));
    }

    /*
        Increases player's frontier count by 1. 
        Plays sound of new frontier.
    */
    void frontier() {
        frontier += 1;
    }
};

void getTreasure(Player *p) {
    cout << "Getting Treasure" << endl;
}


