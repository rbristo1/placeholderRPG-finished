#ifndef BATTLE_H
#define BATTLE_H
#include <vector>
#include <string>

#include "AndrewsFiles/Character.h"
#include "AndrewsFiles/Enemy.h"
#include "AndrewsFiles/Player.h"
#include "AndrewsFiles/Action.h"

using namespace std;
class battle {
    public:
        int battleStart(int enemyNumber, Player * player); //large segments taken from game.cpp by Andrew for the battle logic
    private:
        static const vector<vector<string> > battleInterfaceStates; //holds the battle options printed at the bottom of the screen
        void loadBattleInterface(vector<string> * screen, int battleInterfaceState, int enemyNumber, Enemy * enemy, Player * player); //prints the battle screen
        void printBattleText(vector<string> * screen, string text); //prints text in the text box
        void buildBattleInterface(Player * player); //builds the attack options the player has available to them

        //all written by andrew in game.cpp
        bool BattleOver(Player *player, Enemy *enemy); //checks if the battle has ended (player or enemy dead)
        int damageCalc(int attackerATK, int targetDEF, int power); //calculates damage dealt by an attack
        int attack(Character *attacker, Character *target, Action attack, bool * proc); //attacks
        string flee(Player *player, Enemy *enemy, bool &fled); //run from the battle and end early

};
#endif
