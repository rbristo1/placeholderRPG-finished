// This file is no longer in use. It was used by Andrew for testing, and the functions in this file are still in use, but they have been copied over to the battle.cpp,
// which which was made by Ryan and replaced this file. I left it in for grading purposes, just so you know who made what functions. This is where the descriptions of
// all of the functions are, since I made it

#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "Action.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

Game::Game(){}

int Game::damageCalc(int attackerATK, int targetDEF, int power) { // Damage calculation
    int damageDealt = (int) (((float) attackerATK / (float) targetDEF) * (float) power); // Using floats for more precise division, then turn into an int after
    if (damageDealt == 0) { // All attacks should deal at least one damage
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
    if (attack.isMagic()) { // Determines wheter magic attack and defence or regular attack and defence should be used
        attackerATK = attacker->getStat(3); // Get MGA
        targetDEF = target->getStat(4); // Get MGD
    } else {
        attackerATK = attacker->getStat(1); // Get ATK
        targetDEF = target->getStat(2); // Get DEF
    }

    if (target->isDefending()) { // Double defence if the target is defending
        targetDEF *= 2;
    }

    cout << attacker->getName() << " used " << attackName << "!" << endl;
    
    if (power != 0) { // Only run damage calc if the attack is meant to do damage
        damage = damageCalc(attackerATK, targetDEF, power); // Run damage calc
        cout << target->getName() << " takes " << damage << " damage!" << endl;
    }

    cout << target->applyStatus(effectID, modifier, false); // Apply status to target (it will only do something if effectID != 1, and if it is inteded for the target)
    cout << attacker->applyStatus(effectID, modifier, true); // Apply status to attacker (it will only do something if effectID != 1, and if it is inteded for caster)
    
    target->takeDamage(damage);
    
}

int Game::Battle(Player *player, Enemy *enemy){
    int playerTurn;
    bool death = false;
    int turnCount = 0;
    char currentTurn;
    int playerAction;
    int enemyAction;
    bool paralyzed;
    Action enemyMove;
    
    if (player->getStat(5) >= enemy->getStat(5)){ // Check speed to see who goes first
        playerTurn = 0;
    } else {
        playerTurn = 1;
    }

    while (!death) { // When someone dies, stop
        if(turnCount % 2 == playerTurn) {
            currentTurn = 'p'; // It is currently the player's turn
        } else {
            currentTurn = 'e'; // It is currently the enemy's turn
        }

        if (currentTurn == 'p') { // Player turn
            cout << player->getName() << "'s turn!" << endl;

            if (player->isDefending()) { // Only allow the player to defend for one turn
                player->stopDefending();
            }

            cout << player->activateStatus(paralyzed); // Activate the status effect of the player
            //death = BattleOver(); // Check if the battle is over (died from status effect)
            
            if (paralyzed != true) { // Only move if not paralyzed
                cout << "What would you like to do?" << endl << "1. Attack" << endl << "2. Defend" << endl; // Items and fleeing were not yet implemented, check battle
                cin >> playerAction;

                if (playerAction == 1) {

                    cout << "What attack would you like to use?" << endl;  // Get attack
                    for (int i = 0; i < 4; i++) {
                        cout << i + 1 << ". " << player->getAction(i).getName() << endl << endl;
                    }
                    cin >> playerAction;
                    attack(player, enemy, player->getAction(playerAction - 1)); // Use attack
                } else if (playerAction == 2) {
                    cout << endl << player->getName() << " defended!" << endl << endl; // Defend
                    player->defend();
                } else if (playerAction == 0) {
                    player->printStats(); // Print stats (hidden option for debugging)
                }
            }

            paralyzed = false; // Reset for later use
        }



        if (currentTurn == 'e') { // Enemy's turn
            cout << enemy->getName() << "'s turn!" << endl << endl;

            if (enemy->isDefending()) { // Only allow defending for one turn
                enemy->stopDefending();
            }

            cout << enemy->activateStatus(paralyzed); // Activate status
            //death = BattleOver(); // Check if enemy died from status

            if (paralyzed != true) { // Only move if not paralyzed
                enemyAction = rand() % 4; // 1 in 4 chance to defend, otherwise attack
                if(enemyAction != 0) { 
                    enemyMove = enemy->chooseMove(); // Choose random move, then attack with it
                    attack(enemy, player, enemyMove);
                } else {
                    cout << enemy->getName() << " defended!" << endl << endl; // Defend
                    enemy->defend();
                }
            }

            paralyzed = false; // Reset for later use
            
        }
        
        //death = BattleOver(); // Check if battle is over



        
        cout << endl;
        turnCount++;
    }
    return 0;
}
