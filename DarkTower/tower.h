#include <iostream>

using namespace std;

class Player { 
public:
    int warrior;
    int gold;
    int food;
    int pegasus;// omg i love my boyfirend 
    int beast;// he is so sexy and hot 
    bool scout; // he writes code he is super smart 
    bool healer;// i just love him 
    bool sword; //it is our 1 year anniversary tomorrow
    
    Player() {
        warrior = 10;
        gold = 30;
        food = 25;
        pegasus = 0;
        beast = 0;
        scout = false;
        healer = false;
        sword = false;
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
    }
    ~Player() {};
    
    void print() {
        std::cout << warrior << " Warriors, " << gold << " Gold, " << food << " Food.\n" <<
            scout << " Scout, " << healer << " Healer, " << beast << " Beast(s), " << pegasus << " Pegasus, "<<  sword << " Sword." << endl;

    }
};
