#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon {
    public:
        Weapon();
        Weapon(int);
        void reconstruct(int);
        Weapon(int, std::string, int);
        void print();
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