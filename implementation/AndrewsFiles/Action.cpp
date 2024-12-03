#include "Action.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Action::Action() {
    ID = -1;
    actionName = "Invalid Attack";
    magic = false;
    attackPower = -1;
    status = -1;
    statusModifier = -1;
}

Action::Action(int id) {
    ifstream fin;
    fin.open("Actions.txt");
    string temp;
    int idCompare;

    while (getline(fin, temp, '\n')){
        idCompare = stoi(temp.substr(0, 2));
        if (id == idCompare) {
            break;
        }
    }

    stringstream s(temp);
    s >> ID >> actionName >> magic >> attackPower >> status >> statusModifier;

    for (int i = 0; i < actionName.length(); i++){
        if (actionName[i] == '_') {
            actionName[i] = ' ';
        }
    }
}

Action::Action(int id, string Name, bool isMagic, int power, int statusID) {
    ID = id;
    actionName = Name;
    magic = isMagic;
    attackPower = power;
    status = statusID;
}

void Action::print() {
    cout << "ID - " << ID << "    Name - " << actionName << "    Magic - " << magic << "    Power - " << attackPower << "    Status ID - " << status << endl;
}

void Action::reconstruct(int id) {
    ifstream fin;
    fin.open("Actions.txt");
    string temp;
    int idCompare;

    while (getline(fin, temp, '\n')){
        idCompare = stoi(temp.substr(0, 2));
        if (id == idCompare) {
            break;
        }
    }


    stringstream s(temp);
    s >> ID >> actionName >> magic >> attackPower >> status >> statusModifier;

    for (int i = 0; i < actionName.length(); i++){
        if (actionName[i] == '_') {
            actionName[i] = ' ';
        }
    }
}

void Action::setPower(int amount) {
    attackPower = amount;
}

int Action::getID() {
    return ID;
}

string Action::getName() {
    return actionName;
}

void Action::setName(string name) {
    actionName = name;
}

bool Action::isMagic() {
    return magic;
}

int Action::getPower() {
    return attackPower;
}

int Action::getStatus() {
    return status;
}

float Action::getModifier() {
    return statusModifier;
}