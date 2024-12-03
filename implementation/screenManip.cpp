#include "screenManip.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>


using namespace std;

void screenManip::clearScreen(vector<string> * screen) {
    for (int i = 0; i < screen->size(); i++) {
        screen->at(i) = "                                                                                                                                                ";
    }
    return;
}
void screenManip::printScreen(vector<string> * screen) {



    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws); 
    int lines = ws.ws_row;
    int columns = ws.ws_col;
    int l_offset = (columns - (48*3+2))/2;
    string emptySpace;
    string ret;
    for (int j = 0; j < l_offset; j++) {
        emptySpace += " ";
    }
    for (int i = 0; i < (lines-(screen->size()))/2; i++) {
        ret += "\n";
    }
    printf ("lines %d\n", ws.ws_row);
    printf ("columns %d\n", ws.ws_col);
    cout << ret;

    cout << emptySpace << "┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    for (int i = 0; i < screen -> size(); i++) {
        cout << emptySpace << "│" << screen->at(i) << "│" << endl;
    }
    cout << emptySpace << "└────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘" << endl;
    cout << ret;
    return;
    

}
void screenManip::printScreen2(vector<string> * screen) {

    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws); 
    int lines = ws.ws_row;
    int columns = ws.ws_col;
    int l_offset = (columns - (48*3+2))/2;
    string emptySpace;
    string ret;
    for (int j = 0; j < l_offset; j++) {
        emptySpace += " ";
    }
    for (int i = 0; i < (lines-(screen->size()))/2; i++) {
        ret += "\n";
    }
    printf ("lines %d\n", ws.ws_row);
    printf ("columns %d\n", ws.ws_col);
    cout << ret;

    cout << emptySpace << "┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    for (int i = 0; i < screen -> size(); i++) {
        cout << emptySpace << "│";
        for (int j = 0; j < 144; j++) {
            if (screen->at(i)[j] == '~') {
                cout << "│";
            }
            else if (screen->at(i)[j] == '@') {
                cout << "─";
            }
            else if (screen->at(i)[j] == '$') {
                cout << "└";
            }
            else if (screen->at(i)[j] == '^') {
                cout << "┘";
            }
            else if (screen->at(i)[j] == '&') {
                cout << "┌";
            }
            else if (screen->at(i)[j] == '*') {
                cout << "┐";
            }
            else if (screen->at(i)[j] == '(') {
                cout << "├";
            }
            else if (screen->at(i)[j] == ')') {
                cout << "┬";
            }
            else if (screen->at(i)[j] == '{') {
                cout << "┤";
            }
            else if (screen->at(i)[j] == '}') {
                cout << "┴";
            }
            else if (screen->at(i)[j] == '?') {
                cout << "\033[31mp\033[0m";
            }
            else {
                cout << screen->at(i)[j];
            }
        }
        cout << "│" << endl;
    }
    cout << emptySpace << "└────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘" << endl;
    cout << ret;
    return;
    

}
void screenManip::printCenterFirstAvail(vector<string> * screen, int firstLine, string text) {
    screen -> at(firstLine) = "";
    for (int i = 0; i < (144-text.size())/2; i++) {
        screen->at(firstLine) += " ";
    }
    screen->at(firstLine) += text;
    if (text.size() % 2 == 0) {
        for (int i = 0; i < (144-text.size())/2; i++) {
            screen->at(firstLine) += " ";
        }
    }
    else {
        for (int i = 0; i < ((144-text.size())/2)+1; i++) {
            screen->at(firstLine) += " ";
        }
    }
}
