#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "Action.h"

class Character {

    public:
        Character(int, std::string, const int *); // ID, name, stats(MAX_HP, ATK, DEF, MGA, MGD, SPD)
        void die();
        void printStats();
        void takeDamage(int);
        void heal(int);
        int getID();
        std::string getName();
        int getHP();
        void setHP(int);
        int getStat(int);
        void setStat(int, int);
        bool isDead();
        void changeStats(int, int, bool); // Stat to change, amount to change, length to change (-1 for infinite)
        bool isDefending();
        void defend();
        void stopDefending();
        Action getAction(int);
        std::string applyStatus(int, float, bool); // status ID, status Modifier, if this character is the caster of the status
        void resetStatus();
        void resetTempStats();
        std::string activateStatus(bool &);

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
