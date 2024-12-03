#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "Character.h"
#include "Action.h"

class Enemy : public Character {
    public:
        Enemy(int);
        Action chooseMove();
        bool isBoss();
        
    private:
        bool boss;
        
};
#endif