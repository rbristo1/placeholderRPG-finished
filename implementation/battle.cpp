#include "battle.h"
#include "enemies.h"
#include "screenManip.h"
#include <unistd.h>
#include <iostream>
#include <string>
#include "mapMovements.h"
#include "AndrewsFiles/Character.h"
#include "AndrewsFiles/Enemy.h"
#include "AndrewsFiles/Player.h"
#include "AndrewsFiles/Game.h"
#include "AndrewsFiles/Action.h"
#include <cctype>
#include "../miniAudioSounds.h"
#include <thread>


using namespace std;

const vector<vector<string> > battle::battleInterfaceStates = 
{
    {
        "    \x1B[31m┌─────────────────────────────┐\033[0m    ┌─────────────────────────────┐    ┌─────────────────────────────┐    ┌─────────────────────────────┐    ", 
        "    \x1B[31m│\033[0m    _  _   _           _     \x1B[31m│\033[0m    │ ___       __              _ │    │     ___ _                   │    │        ___ _                │    ", 
        "    \x1B[31m│\033[0m   /_\\| |_| |_ __ _ __| |__  \x1B[31m│\033[0m    │|   \\ ___ / _|___ _ _  ___| |│    │     |_ _| |_ ___ _ __       │    │       | __| |___ ___        │    ",
        "    \x1B[31m│\033[0m  / _ \\  _|  _/ _` / _| / /  \x1B[31m│\033[0m    │| |) / -_)  _/ -_) ' \\/ _ ` |│    │      | ||  _/ -_) '  \\      │    │       | _|| / -_) -_)       │    ",
        "    \x1B[31m│\033[0m /_/ \\_\\__|\\__\\__,_\\__|_\\_\\  \x1B[31m│\033[0m    │|___/\\___|_| \\___|_||_\\___,_|│    │     |___|\\__\\___|_|_|_|     │    │       |_| |_\\___\\___|       │    ",
        "    \x1B[31m│\033[0m                             \x1B[31m│\033[0m    │                             │    │                             │    │                             │    ",
        "    \x1B[31m└─────────────────────────────┘\033[0m    └─────────────────────────────┘    └─────────────────────────────┘    └─────────────────────────────┘    "
    },
    {
        "    ┌─────────────────────────────┐    \x1B[31m┌─────────────────────────────┐\033[0m    ┌─────────────────────────────┐    ┌─────────────────────────────┐    ", 
        "    │    _  _   _           _     │    \x1B[31m│\033[0m ___       __              _ \x1B[31m│\033[0m    │     ___ _                   │    │        ___ _                │    ", 
        "    │   /_\\| |_| |_ __ _ __| |__  │    \x1B[31m│\033[0m|   \\ ___ / _|___ _ _  ___| |\x1B[31m│\033[0m    │     |_ _| |_ ___ _ __       │    │       | __| |___ ___        │    ",
        "    │  / _ \\  _|  _/ _` / _| / /  │    \x1B[31m│\033[0m| |) / -_)  _/ -_) ' \\/ _ ` |\x1B[31m│\033[0m    │      | ||  _/ -_) '  \\      │    │       | _|| / -_) -_)       │    ",
        "    │ /_/ \\_\\__|\\__\\__,_\\__|_\\_\\  │    \x1B[31m│\033[0m|___/\\___|_| \\___|_||_\\___,_|\x1B[31m│\033[0m    │     |___|\\__\\___|_|_|_|     │    │       |_| |_\\___\\___|       │    ",
        "    │                             │    \x1B[31m│\033[0m                             \x1B[31m│\033[0m    │                             │    │                             │    ",
        "    └─────────────────────────────┘    \x1B[31m└─────────────────────────────┘\033[0m    └─────────────────────────────┘    └─────────────────────────────┘    "
    },
    {
        "    ┌─────────────────────────────┐    ┌─────────────────────────────┐    \x1B[31m┌─────────────────────────────┐\033[0m    ┌─────────────────────────────┐    ", 
        "    │    _  _   _           _     │    │ ___       __              _ │    \x1B[31m│\033[0m     ___ _                   \x1B[31m│\033[0m    │        ___ _                │    ", 
        "    │   /_\\| |_| |_ __ _ __| |__  │    │|   \\ ___ / _|___ _ _  ___| |│    \x1B[31m│\033[0m     |_ _| |_ ___ _ __       \x1B[31m│\033[0m    │       | __| |___ ___        │    ",
        "    │  / _ \\  _|  _/ _` / _| / /  │    │| |) / -_)  _/ -_) ' \\/ _ ` |│    \x1B[31m│\033[0m      | ||  _/ -_) '  \\      \x1B[31m│\033[0m    │       | _|| / -_) -_)       │    ",
        "    │ /_/ \\_\\__|\\__\\__,_\\__|_\\_\\  │    │|___/\\___|_| \\___|_||_\\___,_|│    \x1B[31m│\033[0m     |___|\\__\\___|_|_|_|     \x1B[31m│\033[0m    │       |_| |_\\___\\___|       │    ",
        "    │                             │    │                             │    \x1B[31m│\033[0m                             \x1B[31m│\033[0m    │                             │    ",
        "    └─────────────────────────────┘    └─────────────────────────────┘    \x1B[31m└─────────────────────────────┘\033[0m    └─────────────────────────────┘    "
    },{
        "    ┌─────────────────────────────┐    ┌─────────────────────────────┐    ┌─────────────────────────────┐    \x1B[31m┌─────────────────────────────┐\033[0m    ", 
        "    │    _  _   _           _     │    │ ___       __              _ │    │     ___ _                   │    \x1B[31m│\033[0m        ___ _                \x1B[31m│\033[0m    ", 
        "    │   /_\\| |_| |_ __ _ __| |__  │    │|   \\ ___ / _|___ _ _  ___| |│    │     |_ _| |_ ___ _ __       │    \x1B[31m│\033[0m       | __| |___ ___        \x1B[31m│\033[0m    ",
        "    │  / _ \\  _|  _/ _` / _| / /  │    │| |) / -_)  _/ -_) ' \\/ _ ` |│    │      | ||  _/ -_) '  \\      │    \x1B[31m│\033[0m       | _|| / -_) -_)       \x1B[31m│\033[0m    ",
        "    │ /_/ \\_\\__|\\__\\__,_\\__|_\\_\\  │    │|___/\\___|_| \\___|_||_\\___,_|│    │     |___|\\__\\___|_|_|_|     │    \x1B[31m│\033[0m       |_| |_\\___\\___|       \x1B[31m│\033[0m    ",
        "    │                             │    │                             │    │                             │    \x1B[31m│\033[0m                             \x1B[31m│\033[0m    ",
        "    └─────────────────────────────┘    └─────────────────────────────┘    └─────────────────────────────┘    \x1B[31m└─────────────────────────────┘\033[0m    "
    }
};
vector<string> battleSubMenuInterface {
    "            > option1                             option2                             option3                             option4               ",
    "              option1                           > option2                             option3                             option4               ",
    "              option1                             option2                           > option3                             option4               ",
    "              option1                             option2                             option3                           > option4               "
};

bool battle::BattleOver(Player *player, Enemy *enemy){
    if (player->isDead()) {
        //cout << player->getName() << " loses!" << endl;
        return true;
    } else if (enemy->isDead()) {
        //cout << player->getName() << " wins!" << endl;
        return true;
    
    }
    return false;
}
int battle::damageCalc(int attackerATK, int targetDEF, int power) {
    float first = ((float)attackerATK / (float)targetDEF);

    int damageDealt = first * power;
    if (damageDealt == 0) {
        damageDealt = 1;
    }
    return damageDealt;

}

int battle::attack(Character *attacker, Character *target, Action attack, bool * proc) {
    (*proc) = false;
    int attackerATK;
    int targetDEF;
    int damage = 0;
    int power = attack.getPower();
    int effectID = attack.getStatus();
    float modifier = attack.getModifier();
    string attackName = attack.getName();
    if (attack.isMagic()) {
        attackerATK = attacker->getStat(3); // Get MGA
        targetDEF = target->getStat(4); // Get MGD
    } else {
        attackerATK = attacker->getStat(1); // Get ATK
        targetDEF = target->getStat(2); // Get DEF
    }

    if (target->isDefending()) {
        targetDEF *= 2;
    }

    cout << attacker->getName() << " used " << attackName << "!" << endl;
    
    if (power != 0) {
        damage = damageCalc(attackerATK, targetDEF, power);
        cout << target->getName() << " takes " << damage << " damage!" << endl;
    }
    cout << "test";
    string temp;
    temp = target->applyStatus(effectID, modifier, false);
    if (temp != "") {
        (*proc) = true;
    }
    temp = attacker->applyStatus(effectID, modifier, true);
    if (temp != "") {
        (*proc) = true;
    }
    cout << "test";
    
    target->takeDamage(damage);
    return damage;
}

string battle::flee(Player *player, Enemy *enemy, bool &fled) {
    int fleeChance = min(100, max(0, (player->getStat(5) / enemy->getStat(5)) * 50)); // Min an Max make sure that minimum flee chance is 0%, and max flee chance is 100%
    int chance = rand() % 100;
    if (chance < fleeChance) {
        fled = true;
        return player->getName() + " fled!";
    }
    return player->getName() + " couldn't flee!";

}

//loads the battle interface into the screen vector
void battle::loadBattleInterface(vector<string> * screen, int battleInterfaceState, int enemyNumber, Enemy * enemy, Player * player) {
    
    screenManip sm;
    enemyVector ev;
    //finds the size of the enemy art
    int size = ev.enemies[enemyNumber].size();

    //maximum size for an enemy on the screen
    if (size > 35) {
        size = 35;
    }

    //sets the enemy window to the proper enemy art
    for (int i = 2; i<size+2; i++) {
        int offset1 = 0;
        int offset2 = 0;

        offset1 = (144 - ev.enemies[enemyNumber][i-2].size()) / 2;
        if (ev.enemies[enemyNumber][i-2].size() % 2 != 0) {
            offset2 = ((144 - ev.enemies[enemyNumber][i-2].size()) / 2) + 1;
        }
        else {
            offset2 = ((144 - ev.enemies[enemyNumber][i-2].size()) / 2);
        }
        screen->at(i) = "";
        for (int j = 0; j < offset1; j++) {
            screen->at(i) += " ";
        }
        
        screen->at(i) += ev.enemies[enemyNumber][i-2]; 
        for (int j = 0; j < offset2; j++) {
            screen->at(i) += " ";
        }
    }
    //top border for text window
    screen -> at(36) = "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────";

    //bottom border for text window
    screen -> at(40) = "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────";

    //loads player options at the bottom of the screen
    for (int i = 0; i<battleInterfaceStates[0].size(); i++) {
        screen->at(42+i) = battleInterfaceStates[battleInterfaceState][i];
    }
    int decrease = 0;
    string HPstats1 = "Your HP: ";
    HPstats1 += to_string(player->getHP());
    HPstats1 += "/";
    HPstats1 += to_string(player->getStat(0));
    string HPstats2 = "Enemy HP: ";
    HPstats2 += to_string(enemy->getHP());
    HPstats2 += "/";
    HPstats2 += to_string(enemy->getStat(0));
    string concat = HPstats1;
    for (int i = 0; i < (144-HPstats1.size()-HPstats2.size()); i++) {
        concat += " ";
    }
    concat += HPstats2;
    screen->at(49) = concat;

    //prints
    sm.printScreen(screen);
    return;
}

int battle::battleStart(int enemyNumber, Player * player) {
    int playerTurn;
    bool death = false;
    int turnCount = 0;
    char currentTurn;
    int playerAction;
    int enemyAction;
    bool paralyzed;
    Action playerMove;
    Action enemyMove;
    Enemy enemy(enemyNumber);
    //Game mainGame(0);
    (void) playerMove;
    
    if (player->getStat(5) >= enemy.getStat(5)){
        playerTurn = 0;
    } else {
        playerTurn = 1;
    }

    vector<string> screen2;
    screen2.resize(50);
    
    
    screenManip sm;
    mini sounds;
    mapMovements mm;
    battle bt;
    sm.clearScreen(&screen2);
    bt.loadBattleInterface(&screen2, 0, enemyNumber, &enemy, player);
    bt.buildBattleInterface(player);
    string initInput = "A ";
    initInput += enemy.getName();
    initInput += " moves to attack!";
    bt.printBattleText(&screen2, initInput);
    sm.printScreen(&screen2);
    for (int i =0; i< 4; i++) {
        cout << battleSubMenuInterface[i] << endl;
    }
    int lastInput = 0;
    int lastInput2 = 0;
    int submenu = 0;
    string battle1 = "Fight.wav";
    string battle2 = "BossBattle.wav";
    string battle3 = "BossBattleIntro.wav";
    string battle4 = "FinalBossBattle.wav";
    thread music2;
    int loop = 0;
    bool stop = false;
    do{
        
        if (loop == 0) {
            if (enemy.isBoss() == false) {
                stop = true;
                //music2.join();
                stop = false;
                thread music(&mini::playMenuTheme, &sounds, &stop, battle1.data());
                swap(music, music2);
            }
            else if (enemy.isBoss() == true && enemy.getID() == 13) {
                stop = true;
                //music2.join();
                stop = false;
                thread music(&mini::playBossTheme, &sounds, &stop, battle3.data(), battle4.data());
                swap(music, music2);
            }
            else {
                stop = true;
                //music2.join();
                stop = false;
                thread music(&mini::playMenuTheme, &sounds, &stop, battle2.data());
                swap(music, music2);
            }
            loop = 1;
        }
        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
        if(turnCount % 2 == playerTurn) {
            currentTurn = 'p'; // It is currently the player's turn
        } else {
            currentTurn = 'e'; // It is currently the enemy's turn
        }
        if (currentTurn == 'p') {

            if (player->isDefending()) {
                player->stopDefending();
            }

            player->activateStatus(paralyzed);
            death = BattleOver(player, &enemy);
            bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
            
            if (paralyzed != true) {
                //cout << "What would you like to do?" << endl << "1. Attack" << endl << "2. Defend" << endl;
                //cin >> playerAction;
                do {
                    double microsecond = 1000000;
                    usleep(0.03125 * microsecond);//sleeps for 3 second
                    char input = getchar();
                    //input = getchar();
    
                    

                    if (input == 'd' && lastInput != 3 && submenu == 0) {
                        lastInput++;
                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                        //printScreen(&screen);
                    }
                    else if (input == 'a' && lastInput != 0 && submenu == 0) {
                        lastInput--;
                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                        
                    }
                    else if (input == 'd' && lastInput2 != 3 && submenu == 1 && lastInput2 < player->numLearned) {
                        lastInput2++;
                        bt.printBattleText(&screen2, battleSubMenuInterface[lastInput2]);
                        sm.printScreen(&screen2);
                    }
                    else if (input == 'a' && lastInput2 != 0 && submenu == 1) {
                        lastInput2--;
                        bt.printBattleText(&screen2, battleSubMenuInterface[lastInput2]);
                        sm.printScreen(&screen2);
                    }
                    else if (input == 'q' && submenu == 1) {
                        bt.printBattleText(&screen2, "");
                        sm.printScreen(&screen2);
                        lastInput2 = 0;
                        submenu = 0;
                    }
                    //0 = attack state, 1 = defend state, 2 = item state, 3 = flee state
                    else if (input == '\n' && submenu == 0) {
                        if (lastInput == 0) {
                            bt.printBattleText(&screen2, battleSubMenuInterface[0]);
                            sm.printScreen(&screen2);
                            submenu = 1;

                            continue;
                        }
                        else if (lastInput == 1) {
                            player->defend();
                            lastInput = 0;
                            lastInput2 = 0;
                            submenu = 0;
                            string temp = player->getName();
                            temp += " Defended!";
                            bt.printBattleText(&screen2, temp);
                            sm.printScreen(&screen2);
                            usleep(2*microsecond);
                            /*bt.printBattleText(&screen2, battleSubMenuInterface[0]);
                            sm.printScreen(&screen2);
                            submenu = 1;*/

                            break;
                        }
                        else if (lastInput == 2) {
                            lastInput = 0;
                            lastInput2 = 0;
                            submenu = 0;
                            vector<string> inventory = mm.maps[0];
                            inventory[10] = "                                                  Inventory: (numbers to use item, q to exit)                                                   ";

                            for (int j = 0; j<4; j++) {
                                string temp = player->getInventoryName(j);
                                if (temp == "Invalid Item") {
                                    inventory[15+j] = "                                                                  " + to_string(j+1) + ". Empty                                                                      ";
                                }
                                else {
                                    inventory[15+j] = " ";
                                    if (player->getInventoryName(j) == "HP Scroll" || player->getInventoryID(j) == 12) {
                                        for (int i = 2; i < (144-temp.size()-3)/2; i++) {
                                            inventory[15+j] += " ";
                                        }
                                    }
                                    else {
                                        for (int i = 0; i < (144-temp.size()-3)/2; i++) {
                                            inventory[15+j] += " ";
                                        }
                                    }
                                    
                                    inventory[15+j] += to_string(j+1);
                                    inventory[15+j] += ". ";
                                    inventory[15+j] += temp;
                                    if ((temp.size()) % 2 == 0) {
                                        for (int i = 0; i < (144-temp.size()-3)/2; i++) {
                                            inventory[15+j] += " ";
                                        }
                                    }
                                    else {
                                        for (int i = 0; i < ((144-temp.size()-3)/2)+1; i++) {
                                            inventory[15+j] += " ";
                                        }
                                    }
                                }
                            }
                            
                            string temp = "HP: ";
                            temp += to_string(player->getHP());
                            temp += "/";
                            temp += to_string(player->getStat(0));
                            inventory[25] = "";
                            for (int i = 0; i < (144-temp.size())/2; i++) {
                                inventory[25] += " ";
                            }
                            inventory[25] += temp;
                            if (temp.size() % 2 == 0) {
                                for (int i = 0; i < (144-temp.size())/2; i++) {
                                    inventory[25] += " ";
                                }
                            }
                            else {
                                for (int i = 0; i < ((144-temp.size())/2)+1; i++) {
                                    inventory[25] += " ";
                                }
                            }
                            sm.printScreen(&inventory);
                            char input2;
                            string temp2;
                            while (true) {
                                input2 = getchar();
                                if (input2 == 'q') {
                                    bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                    break;
                                }
                                else if (input2 == '1') {
                                    int temp3 = player->getInventoryID(0);
                                    temp2 = player->useItem(0, 0);
                                    buildBattleInterface(player);
                                    if (temp3==12) {
                                        stop = true;
                                        music2.join();
                                        printBattleText(&screen2, "You feel the power of the Scroll of Seg Fault swirl around you.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "You begin to lift into the air.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "The power surges through you, and your eyes begin to glow.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "Your limbs go numb, and you feel the ultimate power you have always desired in your grasp, and then it happens.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "You...");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        *(int*)0 = 0;
                                    }
                                    if (temp != "") {
                                        printBattleText(&screen2, temp);
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        //usleep(2*microsecond);
                                    }
                                    
                                    break;
                                }
                                else if (input2 == '2') {
                                    int temp3 = player->getInventoryID(1);
                                    temp2 = player->useItem(1, 0);
                                    buildBattleInterface(player);
                                    if (temp3==12) {
                                        stop = true;
                                        music2.join();
                                        printBattleText(&screen2, "You feel the power of the Scroll of Seg Fault swirl around you.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "You begin to lift into the air.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "The power surges through you, and your eyes begin to glow.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "Your limbs go numb, and you feel the ultimate power you have always desired in your grasp, and then it happens.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "You...");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        *(int*)0 = 0;
                                    }
                                    if (temp != "") {
                                        printBattleText(&screen2, temp);
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);;
                                        //usleep(2*microsecond);
                                    }
                                    break;
                                }
                                else if (input2 == '3') {
                                    int temp3 = player->getInventoryID(2);
                                    temp2 = player->useItem(2, 0);
                                    buildBattleInterface(player);
                                    if (temp3==12) {
                                        stop = true;
                                        music2.join();
                                        printBattleText(&screen2, "You feel the power of the Scroll of Seg Fault swirl around you.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "You begin to lift into the air.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "The power surges through you, and your eyes begin to glow.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "Your limbs go numb, and you feel the ultimate power you have always desired in your grasp, and then it happens.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "You...");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        *(int*)0 = 0;
                                    }
                                    if (temp != "") {
                                        printBattleText(&screen2, temp);
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        //usleep(2*microsecond);
                                    }
                                    break;
                                }
                                else if (input2 == '4') {
                                    int temp3 = player->getInventoryID(3);
                                    temp2 = player->useItem(3, 0);
                                    buildBattleInterface(player);
                                    if (temp3==12) {
                                        stop = true;
                                        music2.join();
                                        printBattleText(&screen2, "You feel the power of the Scroll of Seg Fault swirl around you.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "You begin to lift into the air.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "The power surges through you, and your eyes begin to glow.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "Your limbs go numb, and you feel the ultimate power you have always desired in your grasp, and then it happens.");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        printBattleText(&screen2, "You...");
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        usleep(4*microsecond);
                                        *(int*)0 = 0;
                                    }
                                    if (temp != "") {
                                        printBattleText(&screen2, temp);
                                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                        //usleep(2*microsecond);
                                    }
                                    break;
                                }
                            }
                            if ((input2 == '1' || input2 == '2' || input2 == '3' || input2 == '4') && temp2 == "") {
                                printBattleText(&screen2, "");
                                bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);

                            }
                            if ((input2 == '1' || input2 == '2' || input2 == '3' || input2 == '4') && temp2 != "") {
                                printBattleText(&screen2, temp2);
                                bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                                usleep(2*microsecond);
                                break;
                            }
                            

                        
                            /*bt.printBattleText(&screen2, battleSubMenuInterface[0]);
                            sm.printScreen(&screen2);
                            submenu = 1;*/
                        }
                        else {
                            lastInput = 0;
                            lastInput2 = 0;
                            submenu = 0;
                            bool fled = false;
                            /*bt.printBattleText(&screen2, battleSubMenuInterface[0]);
                            sm.printScreen(&screen2);
                            submenu = 1;*/
                            printBattleText(&screen2, flee(player, &enemy, fled));
                            sm.printScreen(&screen2);
                            usleep(2*microsecond);
                            if (fled) {
                                return 1;
                            }
                            break;
                            
                        }
                    }
                    else if (input == '\n' && submenu == 1) {
                        bool proc;
                        //attack(player, &enemy, player->getAction(lastInput2));
                        string temp = player->getName();
                        temp += " attacked with ";
                        temp += player->getAction(lastInput2).getName();
                        temp += ", dealing ";
                        int HPbefore = player->getHP();

                        temp += to_string(attack(player, &enemy, player->getAction(lastInput2), &proc));
                        int HPafter = player->getHP();
                        temp += " damage";

                        if (player->getAction(lastInput2).getStatus() == 0 && proc == true) {
                            temp += " and raised their attack!";
                        }
                        else if (player->getAction(lastInput2).getStatus() == 1 && proc == true) {
                            temp += " and raised their defence!";
                        }
                        else if (player->getAction(lastInput2).getStatus() == 2 && proc == true) {
                            temp += " and raised their magic attack!";
                        }
                        else if (player->getAction(lastInput2).getStatus() == 3 && proc == true) {
                            temp += " and raised their magic defence!";
                        }
                        else if (player->getAction(lastInput2).getStatus() == 4 && proc == true) {
                            temp += " and raised their speed!";
                        }
                        else if (player->getAction(lastInput2).getStatus() == 5 && proc == true) {
                            temp += " and lowered " + enemy.getName() + "'s attack!";
                        }
                        else if (player->getAction(lastInput2).getStatus() == 6 && proc == true) {
                            temp += " and lowered " + enemy.getName() + "'s defence!";
                        }
                        else if (player->getAction(lastInput2).getStatus() == 7 && proc == true) {
                            temp += " and lowered " + enemy.getName() + "'s magic attack!";
                        }
                        else if (player->getAction(lastInput2).getStatus() == 8 && proc == true) {
                            temp += " and lowered " + enemy.getName() + "'s magic defence!";
                        }
                        else if (player->getAction(lastInput2).getStatus() == 9 && proc == true) {
                            temp += " and lowered " + enemy.getName() + "'s speed!";
                        }
                        else if (player->getAction(lastInput2).getStatus() == 10 && proc == true) {
                            temp += " and inflicting paralysis!";
                        }
                        else if (player->getAction(lastInput2).getStatus() == 11 && proc == true) {
                            temp += " and inflicting bleed!";
                        }
                        else if (player->getAction(lastInput2).getStatus() == 12 && proc == true) {
                            temp += " and inflicting burn!";
                        }
                        else if (player->getAction(lastInput2).getStatus() == 14 && proc == true) {
                            temp += " and receieved ";
                            temp += to_string(HPbefore-HPafter);
                            temp += " damage in recoil";
                        }
                        else if (player->getAction(lastInput2).getStatus() == 15 && proc == true) {
                            temp += " and inflicting slow!";
                        }
                        else {
                            temp += "!";
                        }
                        printBattleText(&screen2, temp);
                        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
                        usleep(2*microsecond);
                        lastInput = 0;
                        lastInput2 = 0;
                        submenu = 0;
                        break;
                    }
                } while (true);
            }
            

            paralyzed = false;
        }
        if (currentTurn == 'e') {
            //cout << enemy->getName() << "'s turn!" << endl << endl;
            int previousHP = player->getHP();

            if (enemy.isDefending()) {
                enemy.stopDefending();
            }

            enemy.activateStatus(paralyzed);
            death = BattleOver(player, &enemy);

            if (paralyzed != true) {
                enemyAction = rand() % 4;
                if(enemyAction != 0) {
                    bool proc;
                    int HPbefore = enemy.getHP();
                    enemyMove = enemy.chooseMove();
                    string temp = enemy.getName();
                    temp += " attacked with ";
                    temp += enemyMove.getName();
                    temp+= ", dealing ";
                    temp += to_string(attack(&enemy, player, enemyMove, &proc));
                    int HPafter = enemy.getHP();
                    temp += " damage";
                    if (enemyMove.getStatus() == 0 && proc == true) {
                        temp += " and raised their attack!";
                    }
                    else if (enemyMove.getStatus() == 1 && proc == true) {
                        temp += " and raised their defence!";
                    }
                    else if (enemyMove.getStatus() == 2 && proc == true) {
                        temp += " and raised their magic attack!";
                    }
                    else if (enemyMove.getStatus() == 3 && proc == true) {
                        temp += " and raised their magic defence!";
                    }
                    else if (enemyMove.getStatus() == 4 && proc == true) {
                        temp += " and raised their speed!";
                    }
                    else if (enemyMove.getStatus() == 5 && proc == true) {
                        temp += " and lowered " + player->getName() + "'s attack!";
                    }
                    else if (enemyMove.getStatus() == 6 && proc == true) {
                        temp += " and lowered " + player->getName() + "'s defence!";
                    }
                    else if (enemyMove.getStatus() == 7 && proc == true) {
                        temp += " and lowered " + player->getName() + "'s magic attack!";
                    }
                    else if (enemyMove.getStatus() == 8 && proc == true) {
                        temp += " and lowered " + player->getName() + "'s magic defence!";
                    }
                    else if (enemyMove.getStatus() == 9 && proc == true) {
                        temp += " and lowered " + player->getName() + "'s speed!";
                    }
                    else if (enemyMove.getStatus() == 10 && proc == true) {
                        temp += " and inflicting paralysis!";
                    }
                    else if (enemyMove.getStatus() == 11 && proc == true) {
                        temp += " and inflicting bleed!";
                    }
                    else if (enemyMove.getStatus() == 12 && proc == true) {
                        temp += " and inflicting burn!";
                    }
                    else if (enemyMove.getStatus() == 14 && proc == true) {
                        temp += " and receieved ";
                        temp += to_string(HPbefore-HPafter);
                        temp += " damage in recoil";
                    }
                    else if (enemyMove.getStatus() == 15 && proc == true) {
                        temp += " and inflicting slow!";
                    }
                    else {
                        temp += "!";
                    }
                    printBattleText(&screen2, temp);
                } else {
                    string temp = enemy.getName();
                    temp += " Defended!";
                    printBattleText(&screen2, temp);
                    int previousHP = player->getHP();
                    enemy.defend();
                    int currentHP = player->getHP();
                    if (previousHP < currentHP) {
                        player->setHP(previousHP);
                    }

                }
            }
            else {
                string temp = enemy.getName();
                temp += " is paralyzed!";
                printBattleText(&screen2, temp);
            }

            paralyzed = false;
            
        }
        cout << "test";
        death = BattleOver(player, &enemy);
        cout << "test";



        
        cout << "test";
        turnCount++;
        
        

    } while (!death);
    string temp;
    if (player->isDead()) {
        temp = player->getName();
    }
    else {
        temp = enemy.getName();
    }
    player -> resetStatus();
    player->resetTempStats();
    temp += " has been slain!";
    printBattleText(&screen2, temp);
    bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);

    usleep(2*1000000);
    if (!player->isDead()) {
        temp = player->gainRandomPotion();

        if (temp == "Inventory Full!") {
            temp = player->getName();
            temp += " found an item, but their inventory was full so they had to leave it behind.";
        }
        else {
            temp += "!";
        }
        printBattleText(&screen2, temp);
        bt.loadBattleInterface(&screen2, lastInput, enemyNumber, &enemy, player);
        usleep(2*1000000);
    }
    


    loop = 1;
    stop = true;
    music2.join();

    return 0;
}
void battle::printBattleText(vector<string> * screen, string text) {
    screen -> at(38) = "";
    for (int i = 0; i < (144-text.size())/2; i++) {
        screen->at(38) += " ";
    }
    screen->at(38) += text;
    if (text.size() % 2 == 0) {
        for (int i = 0; i < (144-text.size())/2; i++) {
            screen->at(38) += " ";
        }
    }
    else {
        for (int i = 0; i < ((144-text.size())/2)+1; i++) {
            screen->at(38) += " ";
        }
    }
}
void battle::buildBattleInterface(Player * player) {
    for (int i = 0; i<4; i++) {
        battleSubMenuInterface[i] = "";
        /*for (int j = 0; j < (34-player->getAction(0).getName().size())/2; j++) {
            battleSubMenuInterface[i] += " ";

        }*/
        if (i == 0) {
            battleSubMenuInterface[i] += "> ";
        }
        else {
            battleSubMenuInterface[i] += "  ";
        }
        if (player->getAction(0).getName() != "Invalid Attack") {
            battleSubMenuInterface[i] += player->getAction(0).getName();
            for (int j = 0; j < (36-player->getAction(0).getName().size())/2; j++) {
                battleSubMenuInterface[i] += " ";

            }
        }
        else {
            for (int j = 0; j < 36/2; j++) {
                battleSubMenuInterface[i] += " ";
            }
        }
        
        
        
        if (player->getAction(1).getName() != "Invalid Attack") {
            //battleSubMenuInterface[i] += player->getAction(1).getName();
            for (int j = 0; j < (34-player->getAction(1).getName().size())/2; j++) {
                battleSubMenuInterface[i] += " ";

            }
        }
        else {
            for (int j = 0; j < 34/2; j++) {
                battleSubMenuInterface[i] += " ";

            }
        }
        
        if (i == 1) {
            battleSubMenuInterface[i] += "> ";
        }
        else {
            battleSubMenuInterface[i] += "  ";
        }
        if (player->getAction(1).getName() != "Invalid Attack") {
            battleSubMenuInterface[i] += player->getAction(1).getName();
            for (int j = 0; j < (36-player->getAction(1).getName().size())/2; j++) {
                battleSubMenuInterface[i] += " ";

            }
        }
        else {
            for (int j = 0; j < 36/2; j++) {
                battleSubMenuInterface[i] += " ";

            }
        }
        if (player->getAction(2).getName() != "Invalid Attack") {
            for (int j = 0; j < (34-player->getAction(2).getName().size())/2; j++) {
                battleSubMenuInterface[i] += " ";

            }
        }
        else {
            for (int j = 0; j < (34)/2; j++) {
                battleSubMenuInterface[i] += " ";

            }
        }
        
        if (i == 2) {
            battleSubMenuInterface[i] += "> ";
        }
        else {
            battleSubMenuInterface[i] += "  ";
        }
        if (player->getAction(2).getName() != "Invalid Attack") {
            battleSubMenuInterface[i] += player->getAction(2).getName();
            for (int j = 0; j < (36-player->getAction(2).getName().size())/2; j++) {
                battleSubMenuInterface[i] += " ";

            }
        }
        else {
            for (int j = 0; j < (36)/2; j++) {
                battleSubMenuInterface[i] += " ";

            }
        }
        if (player->getAction(3).getName() != "Invalid Attack") {
            for (int j = 0; j < (34-player->getAction(3).getName().size())/2; j++) {
                battleSubMenuInterface[i] += " ";

            }
        }
        else {
            for (int j = 0; j < (34)/2; j++) {
                battleSubMenuInterface[i] += " ";

            }
        }
        
        if (i == 3) {
            battleSubMenuInterface[i] += "> ";
        }
        else {
            battleSubMenuInterface[i] += "  ";
        }
        if (player->getAction(3).getName() != "Invalid Attack") {
            battleSubMenuInterface[i] += player->getAction(3).getName();
        }
        else {

        }
        /*for (int j = 0; j < (36-player->getAction(3).getName().size())/2; j++) {
            battleSubMenuInterface[i] += " ";

        }*/
        

    }
    
}

