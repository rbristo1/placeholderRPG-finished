#ifndef MAPMOVEMENTS_H
#define MAPMOVEMENTS_H
#include <vector>
#include <string>
using namespace std;
class mapMovements {
    public:
        static vector<vector<string> > maps;
        int gameStart(vector<string> * screen);
        vector<string> mapText(vector<string> * screen, string temp);
    private:

};
#endif