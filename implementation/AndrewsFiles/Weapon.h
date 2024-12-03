#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon {
    public:
        Weapon();
        Weapon(int);
        void reconstruct(int); // Same as constructor, used to avoid dynamic memory allocation
        Weapon(int, std::string, int); // Custom constructor
        void print(); // Used for testing only

        // Access and set variables
        int getID();
        std::string getName();
        int getDamage();
        void setID(int);
        void setName(std::string);
        void setDamage(int);

    private:
        int ID;
        std::string name;
        int damage;
};

#endif