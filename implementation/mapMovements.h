#ifndef MAPMOVEMENTS_H
#define MAPMOVEMENTS_H
#include <vector>
#include <string>
using namespace std;
class mapMovements {
    public:
        int gameStart(vector<string> * screen); // starts the game on the first map
        static vector<vector<string> > maps; // holds the 16 maps for the game
    private:
        int keysCollected;
        int keysUsed;
        vector<string> mapText(vector<string> * screen, string temp); // writes important text to the bottom of the screen

};
#endif