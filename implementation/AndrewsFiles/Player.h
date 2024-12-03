#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Weapon.h"
#include "Item.h"
#include <string>
#include <vector>


class Player : public Character {
    friend class Game;
    public:
        Player(std::string, int); // Constructor

        void resetBasicAttack(); // Reconstructs basic attack, used when weapon is changed
        std::string learnNewMove(int);
        std::string learnRandomMove();
        int getNumLearned();
        void print();
        int chooseUnlearnedAction();

        std::string getInventoryName(int);
        int getInventoryID(int);
        std::string gainItem(int);
        std::string gainRandomItem();
        std::string useItem(int, int);
        std::string getNextWeapon();
        
        std::string gainRandomPotion();
        std::string gainRandomScroll();
        int numLearned;
        
        Weapon weapon;
    protected:
        Item inventory[4]; // A list of the items the player is holding

        int playerClass; // 0 - Barbarian   1 - Fighter    2 - Archer   3 - Mage
        std::string className;

        //Weapon weapon; // Equipped weapon

        int learnableActions[4]; // An array of the IDs of the actions available to learn - class dependent, used for skill scroll item implementations
        std::vector<int> unlearnedActions;
        


};
#endif
