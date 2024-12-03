// This file is no longer in use. It was used by Andrew for testing, and the functions in this file are still in use, but they have been copied over to the battle.cpp,
// which which was made by Ryan and replaced this file. I left it in for grading purposes, just so you know who made what functions. This is where the descriptions of
// all of the functions are, since I made it

#ifndef GAME_H
#define GAME_H

#include <string>

class Game {

    public:
        Game();
        int Battle(Player*, Enemy*); // Runs the battle
        int damageCalc(int, int, int);
        void attack(Character*, Character*, Action); // Mediates between the player and enemy for attacking
    private:
        
};
#endif
