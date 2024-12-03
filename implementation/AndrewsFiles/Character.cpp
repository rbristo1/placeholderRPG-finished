#include "Character.h"
#include "Action.h"
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

Character::Character(int id, string characterName, const int* statArray){
    srand(time(NULL));

    ID = id;

    // Set player name
    name = characterName;
    
    // Set stats
    for (size_t i = 0; i < sizeof(stats) / sizeof(stats[0]); i++) { // Loop through stats (adjusts in case I add more)
        if (statArray != nullptr) {
            stats[i] = statArray[i]; // Set all other stats
        }
        temporaryStatChanges[i] = 0;
    }

    dead = false;
    status = -1;
}


void Character::die() {
    cout << name << " died!" << endl;
    dead = true;
}

void Character::printStats() {
    cout << "ID: " << ID << "    Name: " << name << "    HP: " << hp << "/" << stats[0] << "    ATK: " << stats[1] << " + " << temporaryStatChanges[1] <<
    "    DEF: " << stats[2] << " + " << temporaryStatChanges[2] << "    MGA: " << stats[3] << " + " << temporaryStatChanges[3] << "    MGD: " << stats[4] <<
    " + " << temporaryStatChanges[4] << "    SPD: " << stats[5] << " + " << temporaryStatChanges[5] << endl;
}


void Character::takeDamage(int amount) {
    hp -= amount;
    if (hp <= 0) {
        die();
    }
}

void Character::heal(int amount) {
    hp += amount;
    if (hp > stats[0]) {
        hp = stats[0];
    }
}

int Character::getID() {
    return ID;
}


string Character::getName() {
    return name;
}

int Character::getHP() {
    return hp;
}

void Character::setHP(int value) {
    hp = value;
}

int Character::getStat(int id) {
    return stats[id] + temporaryStatChanges[id];
}

void Character::setStat(int id, int value) {
    stats[id] = value;
}

bool Character::isDead() {
    return dead;
}

void Character::changeStats(int stat, int amount, bool permenant) {
    if (permenant) {
        stats[stat] += amount;
    } else {
        temporaryStatChanges[stat] += amount;
    }
}

bool Character::isDefending(){
    return defending;
}

void Character::defend(){
    defending = true;
}

void Character::stopDefending(){
    defending = false;
}

Action Character::getAction(int index) {
    return actions[index];
}

string Character::applyStatus(int id, float modifier, bool caster) {
    // Default (no status) id == -1
    if (id == -1) {
        return "";
    }

    // Raise Stats
    if (id == 0 && caster && temporaryStatChanges[1] <= 0) { // Raise attack
        changeStats(1, stats[1] * modifier, false);
        return name + "'s attack was raised!";
    }

    if (id == 1 && caster && temporaryStatChanges[2] <= 0) { // Raise defense
        changeStats(2, stats[2] * modifier, false);
        return name + "'s defense was raised!";
    }

    if (id == 2 && caster && temporaryStatChanges[3] <= 0) { // Raise magic attack
        changeStats(3, stats[3] * modifier, false);
        return name + "'s magic attack was raised!";
    }

    if (id == 3 && caster && temporaryStatChanges[4] <= 0) { // Raise magic defense
        changeStats(4, stats[4] * modifier, false);
        return name + "'s magic defense was raised!";
    }

    if (id == 4 && caster && temporaryStatChanges[5] <= 0) { // Raise speed
        changeStats(5, stats[5] * modifier, false);
        return name + "'s speed was raised!";
    }

    // Lower Stats
    if (id == 5 && !caster && temporaryStatChanges[1] >= 0) { // Lower attack
        changeStats(1, stats[1] * modifier * -1, false);
        return name + "'s attack was lowered!";
    }

    if (id == 6 && !caster && temporaryStatChanges[2] >= 0) { // Lower defense
        changeStats(2, stats[2] * modifier * -1, false);
        return name + "'s defense was lowered!";
    }

    if (id == 7 && !caster && temporaryStatChanges[3] >= 0) { // Lower magic attack
        changeStats(3, stats[3] * modifier * -1, false);
        return name + "'s magic attack was lowered!";
    }

    if (id == 8 && !caster && temporaryStatChanges[4] >= 0) { // Lower magic defense
        changeStats(4, stats[4] * modifier * -1, false);
        return name + "'s magic defense was lowered!";
    }

    if (id == 9 && !caster && temporaryStatChanges[5] >= 0) { // Lower speed
        changeStats(5, stats[5] * modifier * -1, false);
        return name + "'s speed was lowered!";
    }

    // Apply Paralasis
    if (id == 10 && status == -1 && !caster) {
        int chance = (int) rand() % 100;
        if (chance < modifier) {
            status = 0;
            return name + " was paralyzed!";
        } else {
            return "";
        }
        
    }

    // Apply Bleed
    if (id == 11 && status == -1 && !caster) {
        int chance = rand() % 100;
        if (chance < modifier) {
            status = 1;
            return name + " is bleeding!";
        } else {
            return "";
        }
    }

    // Apply Burn
    if (id == 12 && status == -1 && !caster) {
        int chance = rand() % 100;
        if (chance < modifier) {
            status = 2;
            return name + " was burned!";
        } else {
            return "";
        }
    }

    // Heal
    if (id == 13 && caster) {
        hp += stats[0] * modifier;
        if (hp > stats[0]) {
            hp = stats[0];
        }
        return name + " was healed!";
    }

    // Recoil
    if (id == 14 && caster) {
        takeDamage(hp * modifier);
        return name + " took " + to_string((int) stats[0] * modifier) + " damage in recoil!";
    }

    // Slow
    if (id == 15 && status == -1 && !caster) {
        
        int chance = rand() % 100;
        if (chance < modifier) {
            status = 3;
            return name + " was slowed!";
        }
    }

    return "";
}

string Character::activateStatus(bool &effect) {
    // Paralysis
    if (status == 0) {
        int chance = rand() % 4;
        if (chance == 1) {
            effect = true;
            return name + " is paralyzed! " + name + " can't move!";
        }
    }

    // Bleeding
    if (status == 1) {
        takeDamage((int) stats[0] * 0.125);
        string amount = to_string((int) (stats[0] * 0.125));
        if (amount == "0") {
            amount = "1";
        }
        return name + " is bleeding! " + name + " took " + amount + " damage!";
    }

    // Burn
    if (status == 2) {
        takeDamage((int) stats[0] * 0.125);
        string amount = to_string((int) (stats[0] * 0.125));
        if (amount == "0") {
            amount = "1";
        }
        
        return name + " is bleeding! " + name + " took " + amount + " damage!";
    }

    // Slow
    if (status == 3) {
        status = 4;
        effect = true;
        return name + " is slowed! " + name + " missed their turn!";
    }

    if (status == 4) {
        status = 3;
        return name + " is slowed!";
    }

    return "";
}

void Character::resetStatus() {
    status = -1;
}

void Character::resetTempStats() {
    for (int i = 0; i < 6; i++) {
        temporaryStatChanges[i] = 0;
    }
}