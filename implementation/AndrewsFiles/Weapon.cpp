#include "Weapon.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Weapon::Weapon() {
    ID = -1;
    name = "";
    damage = -1;
}

Weapon::Weapon(int id) {
    ifstream fin;
    fin.open("Weapons.txt");
    string temp;
    int idCompare;

    while (getline(fin, temp, '\n')){
        idCompare = stoi(temp.substr(0, 2));
        if (id == idCompare) {
            break;
        }
    }

    stringstream s(temp);
    s >> ID >> name >> damage;

    for (int i = 0; i < name.length(); i++){ // Replace '_' with ' '
        if (name[i] == '_') {
            name[i] = ' ';
        }
    }
}

void Weapon::reconstruct(int id) {
    ifstream fin;
    fin.open("Weapons.txt");
    string temp;
    int idCompare;

    while (getline(fin, temp, '\n')){
        idCompare = stoi(temp.substr(0, 2));
        if (id == idCompare) {
            break;
        }
    }

    stringstream s(temp);
    s >> ID >> name >> damage;

    for (int i = 0; i < name.length(); i++){ // Replace '_' with ' '
        if (name[i] == '_') {
            name[i] = ' ';
        }
    }
}

Weapon::Weapon(int id, string weaponName, int weaponDamage) {
    ID = id;
    name = weaponName;
    damage = weaponDamage;
}

void Weapon::print() {
    cout << "ID - " << ID << "    Name - " << name << "    Damage - " << damage << endl;
}

int Weapon::getID() {
    return ID;
}

string Weapon::getName() {
    return name;
}

int Weapon::getDamage() {
    return damage;
}

void Weapon::setID(int id) {
    ID = id;
}

void Weapon::setName(string newName) {
    name = newName;
}

void Weapon::setDamage(int newDamage) {
    damage = newDamage;
}