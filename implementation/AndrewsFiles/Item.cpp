#include "Item.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Item::Item() {
    ID = -1;
    name = "Invalid Item";
    effect = -1;
}

Item::Item(int id) {
    ifstream fin;
    fin.open("Items.txt");
    string temp;
    int idCompare;

    while (getline(fin, temp, '\n')){
        idCompare = stoi(temp.substr(0, 2));
        if (id == idCompare) {
            break;
        }
    }

    stringstream s(temp);
    s >> ID >> name >> effect;

    for (int i = 0; i < name.length(); i++){ // Replace '_' with ' '
        if (name[i] == '_') {
            name[i] = ' ';
        }
    }
}

void Item::reconstruct(int id) {
    ifstream fin;
    fin.open("Items.txt");
    string temp;
    int idCompare;

    while (getline(fin, temp, '\n')){
        idCompare = stoi(temp.substr(0, 2));
        if (id == idCompare) {
            break;
        }
    }

    stringstream s(temp);
    s >> ID >> name >> effect;

    for (int i = 0; i < name.length(); i++){ // Replace '_' with ' '
        if (name[i] == '_') {
            name[i] = ' ';
        }
    }
}

Item::Item(int id, string weaponName, int itemEffect) {
    ID = id;
    name = itemEffect;
    effect = itemEffect;
}

void Item::print() {
    cout << "ID - " << ID << "    Name - " << name << "    Effect - " << effect << endl;
}

int Item::getID() {
    return ID;
}

string Item::getName() {
    return name;
}

int Item::getEffect() {
    return effect;
}

void Item::setID(int id) {
    ID = id;
}

void Item::setName(string newName) {
    name = newName;
}