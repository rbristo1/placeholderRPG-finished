#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "Action.h"

// The Character class is used as a sort of parent class for the Player and Enemy classes. The character class is never used directly, but is to simplify the
// similarities between the Player and Enemy classes
class Character {

    public:
        Character(int, std::string, const int *); // ID, name, stats(MAX_HP, ATK, DEF, MGA, MGD, SPD)

        void printStats(); // Used for testing only

        int getID();
        std::string getName();
        int getHP();
        void setHP(int);
        int getStat(int);
        bool isDead();
        bool isDefending();
        Action getAction(int); // Gets action from actions[] array

        void setStat(int, int); 
        void changeStats(int, int, bool); // Stat to change, amount to change, is permanent
        void takeDamage(int); // Changes hp value in conjunction with attack() from battle.cpp
        void heal(int); // Heals hp for item use
        void die(); // Set dead to true
        void defend(); // Set defending to true
        void stopDefending(); // Set defending to false
        void resetTempStats(); // Set all temp stats to 0
        
        std::string applyStatus(int, float, bool); // status ID, status Modifier, if this character is the caster of the status
        void resetStatus(); // Set status to -1
        std::string activateStatus(bool &); // Actually do what the status effect is supposed to do

    protected:
        int ID;
        std::string name;
        int hp;
        int stats[6];
        int temporaryStatChanges[6];
        bool dead;
        Action actions[4]; // An array of all the actions one can take
        int status;
        int weaponDamage;
        bool defending;

};

#endif
