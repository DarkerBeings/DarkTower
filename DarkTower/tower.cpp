#include <iostream>
#include <cstdlib>
#include <string.h>
#include <conio.h>
#include <cmath>
// #ifdef _WIN32
// #include <Windows.h>
// #else
#include <unistd.h>
// #endif
#include "tower.h"

/**
 function for bazaar to ensure consistency in price ranges when setting price.
*/
int bazaarRand(int select) {
    switch (select) {
        case 1: 
            return (rand() % 6) + 5; // 5 to 10
            break;
        case 2: 
            return (rand() % 11) + 16;
            break;
        default:
        return 1;
    }   
}

/*
    Bazaar Function.
    The bazaar is a place for the player to purchase warriors, food, and other helpful assistance for their journey.
    The bazaar will print a list of all 5 items to sell, along with their price.
    It will also include the option to haggle, which when used will decrease the price of a selected item by 1.
    Could be changed to not include options scout, healer, or beast when they have already been bought.
*/
void bazaar(Player *p) {
    int prices[5];
    //warrior
    //5 to 10
    prices[0] = bazaarRand(1);
    //food
    prices[1] = 1;
    // Range 16 to 26
    //scout
    prices[2] = bazaarRand(2);
    //healer
    prices[3] = bazaarRand(2);
    //beast
    prices[4] = bazaarRand(2);
    bool haggle = true; 
    int haggleOdds = 100;
    int select, amount;

    //keep the prices printing as long as you're haggling
    while (haggle) {
        SetColor(1);
        cout << "Bazaar: \n" << "(1) Warrior: " << prices[0] << 
            "\n(2) Food: " << prices[1] << "\n(3) Scout: " << prices[2] <<
            "\n(4) Healer: " << prices[3] << "\n(5) Beast: " << prices[4] << "\n(6) Haggle" << line;

        SetColor(7);
        cout << "Input Select & Amount or Input Haggle & Select as integers in Format: xx yy" << endl;
        cin >> select >> amount;
        if (select == 6) { //If your number is out of bounds, close bazaar
            if (amount < 1 || amount > 5) {
                cout << "Bazaar Closed. You don't even know what you're asking for!" << line;
                return;
            } else if (rand() % 100 > haggleOdds) { //pick a number between 0 and 99. if it is above the hagglecount, close bazaar.
                cout << "Bazaar Closed. You cannot haggle me that much!" << line;
                return;
            }

            switch(amount) { //Decrease the price of the selected haggle by 1
                case 1:
                    if (prices[0] <= 5) {
                        cout << "Bazaar Closed. I Can't Go Lower!" << line; 
                        return;
                     }
                    prices[0]--;
                    break;
                case 2:          
                    if (prices[1] <= 1) {
                        cout << "Bazaar Closed. I Can't Go Lower!" << line; 
                        return; 
                     }
                    prices[1]--;
                    break;
                case 3:
                    if (prices[2] <= 16){
                        cout << "Bazaar Closed. I Can't Go Lower!" << line; 
                        return;
                     }
                    prices[2]--;
                    break;
                case 4:
                    if (prices[3] <= 16) {
                        cout << "Bazaar Closed. I Can't Go Lower!" << line; 
                        return;
                     }
                    prices[3]--;            
                    break;
                case 5:
                    if (prices[4] <= 16) {
                        cout << "Bazaar Closed. I Can't Go Lower!" << line; 
                        return;

                     }
                    prices[4]--;             
                    break;
                default:
                    // cout << "Default switch case haggle" << endl;
                    break;
            }
        }
        
            if (select < 1 || select > 6) { //if your selection is out out bounds, close bazaar.
                cout << "Bazaar Closed. What are you trying to buy?" << line;
                return;
            } 
            if(select != 6) { //either stop haggling or decrease haggling odds
                haggle = false;
            } else {
              haggleOdds -= 25;
            }

        }

        int buyPrice = prices[select - 1] * amount;

        if (buyPrice > p->gold) {
            cout << "Bazaar Closed. You can't afford that much!" << line;
        } else {
            p->gold = (p->gold - buyPrice);
            cout << "Purchase Sucessful" << endl;
            switch(select) {
                case 1:
                    p->warrior = p->warrior + amount;
                    // cout << "Warriors: " << p-> warrior << endl;
                    break;
                case 2:
                    p->food = p->food + amount;
                    // cout << "Food: " << p->food << endl;
                    break;
                case 3:
                    p->scout = true;
                    // cout << "You now have a scout" << endl;
                    break;
                case 4:
                    p->healer = true;
                    // cout << "You now have a healer" << endl;
                    break;
                case 5:
                    p->beast = true;

                    // cout << "Beasts: " << p->beast << endl;
                    break;
                default:
                    cout << "Default switch case buying" << endl;
                    break;
            }
        cout << line;
    }
    


   
}

/*
    Prints out the skirmishes in a fight.
    Prints number of warriors and number of brigands alive during a skirmish. 
    Has time in between for suspense.
    Needs to change to have sound input if a round is won or lost;
*/
void fightPrint(Player *p, int brigs) {
        SetColor(2);
        cout << p->warrior <<endl;
        usleep(2000000);

        SetColor(4);
        cout << brigs << endl;
        usleep(2000000);
        SetColor(7);
}

/*
    Fighting function. 
*/
bool fight(Player *p, int brigs) {
    cout << p->warrior << " warriors, " << brigs << " brigands"<< endl;
    usleep(500000);

    while (p->warrior > 2 ) {
        // random number from range -10 to 100
        // This range ensures that even if the increased odds of winning make the odds over 100, there is still a 5 percent chance to lose.
        int num = (rand() % 106) - 6;
        int limit = 80 + ((p->warrior - brigs) * 2);

        // if rand number is between 0 and 70 + diff of warrior & brigs * multiplier, then warrior wins skirmish
        if (!(num > 0 && num < limit)) {
            p->warrior -= ((rand() % 4) + 1);
            p->warrior = max(p->warrior, 1);
            //Play lose skirmish sound
        } else {
            brigs -= ((rand() % 4) + 1);
            brigs =  max(brigs, 0);
            //Play win skirmish sound
        }
        // SetColor(6);
        // cout << num << ",   " << limit << endl;
        fightPrint(p, brigs);

        if(brigs <= 0) {
        // WIN
        //    fightPrint(p, brigs);
            getTreasure(p);
            p->updateGold(0);
            cout << line;
            return true;
        }
    }
    // LOSE 
    // fightPrint(p, brigs);
    p->updateGold(0);
    cout << "You Have Been Overwhelmed by Brigands! " << p->warrior << " Warriors Left!" << endl;
    return false;
}

/*
    Move Function.
    When a player moves, there are a variety of events that can occur.
    1. Safe. Nothing Happens.
    2. Battle. Fight a battle with brigands of an amount range +/- 3 of your current warrior count.
    3. Lost. Move back a space. If you have a scout then you get another move.
    4. Plague. If you don't have a healer, lose 2 of your warriors. If you have a healer, gain 2 warriors instead.
    5. Dragon. Lose 1/4 of your warriors and gold. If you have a dragonsword, gain the dragon's hoard. 
        After defeating the dragon, a player loses their dragonsword.
    Return true if player gets another turn.
*/
bool move(Player *p) {
    int chance = rand() % 32;

    if (chance < 2) { // dragon
        SetColor(4);
        cout << "Dragon Attack!!" << endl;
        if (p->sword) {
            SetColor(10);
            cout << "You used your sword! The dragon is slain!" << endl;
            p->warrior += p->warrior / 4;
            p->updateGold(p->gold / 4);
        } else {
            cout << "You were overwhelmed by the Dragon! Your warriors and gold were taken!" << endl;
            p->warrior = max(p->warrior - (int) (ceil(p->warrior / 4.0)), 1);
            p->updateGold(-1 * p->gold / 4);
        }
        SetColor(6);
        cout << p->warrior << " Warriors, " << p->gold << " Gold." << endl;
        SetColor(7);
        return false;
    }   
    else if (chance < 7) { // lost
        SetColor(8);
        cout << "You got Lost!" << endl;
        if (p->scout) {
            SetColor(10);
            cout << "Your scout found your way, gain another turn!";
            SetColor(7);
            return true;
        } else {
            cout << "After walking in circles, you find your way back to where you came from! \n Move back to your previous space." << endl;
            SetColor(7);
            return false;
        }
    } 
    else if (chance < 12) { // plague
        SetColor(5);
        cout << "Your crew is infected with the plague!" << endl;
        if (p->healer) {
            SetColor(10);
            cout << "Your healer got rid of the plague. 2 warriors joined your ranks." << endl;
            p->warrior += 2;
        } else {
            cout << "You lost two of your warriors. The rest of your ranks got over themselves." << endl;
            p->warrior = max(p->warrior - 2, 1);
        }
        SetColor(7);
        return false;

    } 
    else if (chance < 22) { //safe
        cout << "You move." << endl;
        return false;
    } else { //battle
        fight(p, p->warrior + (rand() % 7) - 3);

        return false;
    }

    return false;
}


/*
    Tomb / Ruins
    3 Events can happen whenever a player enters a tomb or a ruin.
    1. Deserted. The tomb / ruin is empty, and the player's turn is ended.
    2. Battle. Fight a battle that follows same ruleset as the move function.
    3. Treasure. Earn one of the treasures without needing to fight a battle.
*/
void tombRuins(Player *p) {
    int chance = rand() % 16;


}

/*
    Citadel / Sanctuary
    When a player enters their own citadel or a sanctuary, they will be resupplied with warriors, gold, and / or food.
    If a player has 4 warriors or less, they will be resupplied with warriors.
    If a player has 7 bags of gold or less, they will be resupplied with gold.
    If a player has 5 rations of food or less, they will be resupplied with food.
    If you have a healthy amount of supplies, your turn will end.
    After getting all 3 keys and returning to your home citadel, 
        a player will be heavily supplied with all rations to go and challend the Tower.
*/
void sanctuary(Player *p) {
    //starts off in frontier 0, so a full loop will have frontier be 4;
    bool lastFrontier = (p->frontier % 5) == 4;
    if (!lastFrontier) {
        if (p->warrior <= 4) {
            p->warrior += 4 + rand() % 3;
        } 
        if (p->gold <= 7) {
            p->gold += 7 + rand() % 5;
        } 
        if (p->food <= 5) {
            p->food += 5 + rand() % 10;
        }
    } else {
        p->warrior += rand() % 5 + 10;
        p->updateGold(rand() % 30 + 5);
        p->food += rand() % 10 + 10;
    }
    SetColor(6);
    cout << p->warrior << " Warriors, " << p->gold << " Gold, " << p->food << " Food.\n" << endl;
    SetColor(7);
    return;
}

/*
    Fight the Dark Tower!
*/
bool darkTower(Player *p) {

    return false;
}


/*
    Main function loop.
*/
int main (int argc, char *argv[]) {
    srand(time(0));
    cout << "Input the number of players in your game." << endl;
    int players;
    cin >> players;

    Player p[players];
    for (int i = 0; i < players; i++) {
        p[i].printInventory();
    }

    if (players < 0 || players > 3) {
        players = max(players, 0);
        players = min(players, 3);
    }

    int curPlayer = 0;
    bool gameWin = false;

    while(!gameWin) {
        bool turn = true;

        while(turn) {
            cout << "Player " << curPlayer + 1 << "'s turn.\n" <<
            "(1) Move\n" <<
            "(2) Inventory\n" <<
            "(3) Frontier\n" <<
            "(4) Tomb / Ruin\n" <<
            "(5) Citadel / Sanctuary\n" <<
            "(6) Bazaar\n" <<
            "(7) Dark Tower\n";

            int choice;
            cin >> choice;

            switch(choice) {
                case 1:
                    turn = move(&p[curPlayer]);
                    break;
                case 2:
                    p[curPlayer].printInventory();
                    turn = false;
                    break;
                case 3:
                    p[curPlayer].onFrontier();
                    turn = false;
                    break;
                case 4:
                    tombRuins(&p[curPlayer]);
                    turn = false;
                    break;
                case 5:
                    sanctuary(&p[curPlayer]);
                    turn = false;
                    break;
                case 6:
                    bazaar(&p[curPlayer]);
                    break;
                case 7:
                    gameWin = darkTower(&p[curPlayer]);
                    turn = false;
                    break;
                default:
                    cout << "You cannot do that." << endl;
                    turn = true;
                    break;
            } 


        }

        //Increase the turn count
        cout << -1 * (curPlayer + 1) << endl;        
        curPlayer = (curPlayer + 1) % players;
        // while(cin.get().equals('')) {

        // }
        
    }

    
    return 0;
}

  