#ifndef GAME_H
#define GAME_H

#include <string>

class Game {

    public:
        Game(int);
        int Battle(Player*, Enemy*);
        int damageCalc(int, int, int);
        void attack(Character*, Character*, Action);
        void Overworld();
        bool BattleOver();
    private:
        
};
#endif
