#include "Enemy.h"
#include <sstream>
#include <fstream>

using namespace std;


Enemy::Enemy(int id) : Character(id, "", nullptr){ // Used ChatGPT for help figuring out inheritense with header files
    ifstream fin;
    fin.open("Enemies.txt");
    string temp;
    int idCompare;
    int attackIDs[4] = {-1, -1, -1, -1};

    while (getline(fin, temp, '\n')){
        idCompare = stoi(temp.substr(0, 2));
        if (id == idCompare) {
            break;
        }
    }

    stringstream s(temp);
    s >> ID >> name >> stats[0] >> stats[1] >> stats[2] >> stats[3] >> stats[4] >> stats[5] >> attackIDs[0] >> attackIDs[1] >> attackIDs[2] >> attackIDs[3] >> boss;
    hp = stats[0];

    for (int i = 0; i < 4; i++) {
        if (attackIDs[i] != -1) {
            actions[i].reconstruct(attackIDs[i]);
        }
        
    } 
    for (int i = 0; i < name.length(); i++){
        if (name[i] == '_') {
            name[i] = ' ';
        }
    }
    
}

Action Enemy::chooseMove() {
    int numActions;
    int moveChosen;
    for (numActions = 0; actions[numActions].getID() != -1 && numActions < 4; numActions++) {}
    moveChosen = rand() % numActions;
    return actions[moveChosen];
}

bool Enemy::isBoss() {
    return boss;
}