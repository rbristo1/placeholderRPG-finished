#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "Action.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

Game::Game(int i){}

int Game::damageCalc(int attackerATK, int targetDEF, int power) {
    int damageDealt = (attackerATK / targetDEF) * power;
    if (damageDealt == 0) {
        damageDealt = 1;
    }
    return damageDealt;

}

void Game::attack(Character *attacker, Character *target, Action attack) {
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

    cout << target->applyStatus(effectID, modifier, false);
    cout << attacker->applyStatus(effectID, modifier, true);
    
    target->takeDamage(damage);
    
}

bool Game::BattleOver(/*Player *player, Enemy *enemy*/){
    /*if (player->isDead()) {
        //cout << player->getName() << " loses!" << endl;
        return true;
    } else if (enemy->isDead()) {
        //cout << player->getName() << " wins!" << endl;
        return true;
    }*/
    return false;
}

int Game::Battle(Player *player, Enemy *enemy){
    int playerTurn;
    bool death = false;
    int turnCount = 0;
    char currentTurn;
    int playerAction;
    int enemyAction;
    bool paralyzed;
    Action playerMove;
    Action enemyMove;

    (void) playerMove;
    
    if (player->getStat(5) >= enemy->getStat(5)){
        playerTurn = 0;
    } else {
        playerTurn = 1;
    }

    while (!death) {
        if(turnCount % 2 == playerTurn) {
            currentTurn = 'p'; // It is currently the player's turn
        } else {
            currentTurn = 'e'; // It is currently the enemy's turn
        }

        if (currentTurn == 'p') {
            cout << player->getName() << "'s turn!" << endl;

            if (player->isDefending()) {
                player->stopDefending();
            }

            cout << player->activateStatus(paralyzed);
            death = BattleOver();
            
            if (paralyzed != true) {
                cout << "What would you like to do?" << endl << "1. Attack" << endl << "2. Defend" << endl;
                cin >> playerAction;

                if (playerAction == 1) {

                    cout << "What attack would you like to use?" << endl;
                    for (int i = 0; i < 4; i++) {
                        cout << i + 1 << ". " << player->getAction(i).getName() << endl << endl;
                    }
                    cin >> playerAction;
                    attack(player, enemy, player->getAction(playerAction - 1));
                } else if (playerAction == 2) {
                    cout << endl << player->getName() << " defended!" << endl << endl;
                    player->defend();
                } else if (playerAction == 0) {
                    player->printStats();
                }
            }

            paralyzed = false;
        }



        if (currentTurn == 'e') {
            cout << enemy->getName() << "'s turn!" << endl << endl;

            if (enemy->isDefending()) {
                enemy->stopDefending();
            }

            cout << enemy->activateStatus(paralyzed);
            death = BattleOver();

            if (paralyzed != true) {
                enemyAction = rand() % 4;
                if(enemyAction != 0) {
                    enemyMove = enemy->chooseMove();
                    attack(enemy, player, enemyMove);
                } else {
                    cout << enemy->getName() << " defended!" << endl << endl;
                    enemy->defend();
                }
            }

            paralyzed = false;
            
        }
        
        death = BattleOver();



        
        cout << endl;
        turnCount++;
    }
    return 0;
}
