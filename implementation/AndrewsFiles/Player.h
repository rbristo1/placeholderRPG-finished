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
        std::string learnNewMove(int); // Add new learned move
        std::string learnRandomMove(); // Choose a random move to learn
        int getNumLearned(); // Return number of moves a player has learned
        void print(); // Used for testing only
        int chooseUnlearnedAction(); // Choose a move that the player is capable of learning, but has not done so yet


        std::string getInventoryName(int); // Return the name of the item in a given inventory index
        int getInventoryID(int); // Return the ID of the item in a given inventory index
        std::string gainItem(int); // Add item to inventory
        std::string gainRandomItem(); // Get random item
        std::string useItem(int, int); // Remove item from inventory and active the effects of it
        std::string getNextWeapon(); // Upgrade weapon to next one
        
        std::string gainRandomPotion(); // Get only random potion
        std::string gainRandomScroll(); // Get only random scroll (not skill scroll or scroll of seg fault)
        int numLearned; // The number of moves the player has learned
        
        Weapon weapon; // The weapon the player has equipped
    protected:
        Item inventory[4]; // A list of the items the player is holding

        int playerClass; // 0 - Barbarian   1 - Fighter    2 - Archer   3 - Mage
        std::string className; // Used in print (for testing only)

        //Weapon weapon; // Equipped weapon

        int learnableActions[4]; // An array of the IDs of the actions available to learn - class dependent, used for skill scroll item implementations
        std::vector<int> unlearnedActions; // A vector of the actions the player has not learned yet. The size changes, which is why it is a vector
        


};
#endif
