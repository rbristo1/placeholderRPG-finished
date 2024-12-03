#ifndef SCREENMANIP_H
#define SCREENMANIP_H
#include <vector>
#include <string>
using namespace std;
class screenManip {
    public:
        void clearScreen(vector<string> * screen);
        void printScreen(vector<string> * screen);
        void printScreen2(vector<string> * screen);
        void printCenterFirstAvail(vector<string> * screen, int firstLine, string text);
    private:

};
#endif