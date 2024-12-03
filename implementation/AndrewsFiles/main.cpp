#include "Character.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "Action.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Action attack(0);
    Game mainGame(0);
    Enemy slime(0);
    int choice;

    cout << "Choose Your Class!" << endl << "1. Barbarian" << endl << "2. Knight" << endl << "3. Archer" << endl << "4. Mage" << endl;
    cin >> choice;
    cout << endl;

    Player player("Greg", choice - 1);
    player.print();

    player.learnNewMove(4);
    player.learnNewMove(1);
    player.learnNewMove(2);
    player.learnNewMove(3);

    mainGame.Battle(&player, &slime);
}