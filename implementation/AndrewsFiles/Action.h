#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action {
    public:
        Action(); // Needed to make an array of Actions
        Action(int); // id
        Action(int, std::string, bool, int, int); // id, actionName, magic, attackPower, status
        void print(); // Used for Testing
        void reconstruct(int); // "Reconstructs" an already existing action, used to aviod dynamic memory allocation (because its scary)

        // Access Functions
        int getID();
        std::string getName();
        bool isMagic();
        int getPower();
        float getModifier();
        int getStatus();

        // Set Functions
        void setName(std::string); // Change name (used for basic attack)
        void setPower(int); // Change the attack power (used for basic attack and reckless attack)

    protected:
        int ID;
        std::string actionName;
        bool magic;
        int attackPower;
        int status;
        float statusModifier; // What this does depends on status. It may be the amount a stat is changed by, or the chance for an effect to proc
};
#endif