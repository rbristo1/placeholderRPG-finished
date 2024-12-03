#ifndef BATTLE_H
#define BATTLE_H
#include <vector>
#include <string>
#include "AndrewsFiles/Character.h"
#include "AndrewsFiles/Enemy.h"
#include "AndrewsFiles/Player.h"
#include "AndrewsFiles/Game.h"
#include "AndrewsFiles/Action.h"

using namespace std;
class battle {
    public:
        static const vector<vector<string> > battleInterfaceStates;
        void loadBattleInterface(vector<string> * screen, int battleInterfaceState, int enemyNumber, Enemy * enemy, Player * player);
        int battleStart(int enemyNumber, Player * player);
        void printBattleText(vector<string> * screen, string text);
        void buildBattleInterface(Player * player);
        bool BattleOver(Player *player, Enemy *enemy);
        int damageCalc(int attackerATK, int targetDEF, int power);
        int attack(Character *attacker, Character *target, Action attack, bool * proc);
        string flee(Player *player, Enemy *enemy, bool &fled);
    private:

};
#endif
