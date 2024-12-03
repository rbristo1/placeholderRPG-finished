#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action {
    public:
        Action();
        Action(int); // id
        Action(int, std::string, bool, int, int); // id, actionName, magic, attackPower, status
        void print();
        void reconstruct(int);
        void setPower(int); // Change the attack power (used for basic attack and reckless attack)
        int getID();
        std::string getName();
        void setName(std::string);
        bool isMagic();
        int getPower();
        float getModifier();
        int getStatus();

    protected:
        int ID;
        std::string actionName;
        bool magic;
        int attackPower;
        int status;
        float statusModifier;
};
#endif