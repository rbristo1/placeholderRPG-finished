#ifndef SCREENMANIP_H
#define SCREENMANIP_H
#include <vector>
#include <string>
using namespace std;
class screenManip {
    public:
        void clearScreen(vector<string> * screen); //resets screen to blank
        void printScreen(vector<string> * screen); //prints screen with no processing
        void printScreen2(vector<string> * screen); //prints screen adjusting UTF-8 wall characters to UTF-32
        void printCenterFirstAvail(vector<string> * screen, int firstLine, string text); // used for printing center alligned text
    private:

};
#endif