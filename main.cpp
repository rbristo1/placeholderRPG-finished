

#include "implementation/enemies.h"
#include "implementation/screenManip.h"
#include "implementation/battle.h"
#include "implementation/mapMovements.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <termios.h>
#include "miniAudioSounds.h"
#include <thread>


using namespace std;


vector<string> title = {"\x1B[96m__________.__                      .__           .__       .___            \033[0m",
                        "\x1B[96m\\______   \\  | _____    ____  ____ |  |__   ____ |  |    __| _/___________ \033[0m", 
                        "\x1B[96m |     ___/  | \\__  \\ _/ ___\\/ __ \\|  |  \\ /  _ \\|  |   / __ |/ __ \\_  __ \\\033[0m", 
                        "\x1B[96m |    |   |  |__/ __ \\  \\__\\   ___/|   Y  (  <_> )  |__/ /_/ \\  ___/|  | \\/\033[0m", 
                        "\x1B[96m |____|   |____(____  /\\___  >___  >___|  /\\____/|____/\\____ |\\___  >__|   \033[0m", 
                        "\x1B[96m                    \\/     \\/    \\/     \\/                  \\/    \\/       \033[0m"};

vector<string> gameOver = {
"  ____    _    __  __ _____    _____     _______ ____  ",
" / ___|  / \\  |  \\/  | ____|  / _ \\ \\   / / ____|  _ \\  ",
"| |  _  / _ \\ | |\\/| |  _|   | | | \\ \\ / /|  _| | |_) | ",
"| |_| |/ ___ \\| |  | | |___  | |_| |\\ V / | |___|  _ <  ",
" \\____/_/   \\_\\_|  |_|_____|  \\___/  \\_/  |_____|_| \\_\\ "
};
vector<string> gameWin = {


"__   _____  _   _  __        _____ _   _ _ ",
"\\ \\ / / _ \\| | | | \\ \\      / /_ _| \\ | | |",
" \\ V / | | | | | |  \\ \\ /\\ / / | ||  \\| | |",
"  | || |_| | |_| |   \\ V  V /  | || |\\  |_|",
"  |_| \\___/ \\___/     \\_/\\_/  |___|_| \\_(_)"


};
vector <string> IntroText = {
    "1,000 years ago, the dark Kingdom of Liked Lists ruled the land.",
    "Monsters slaughtered entire villages, spirits made the inhabitants go insane, and a dark blight killed off all of the crops.",
    "It seemed as if the darkness would never end, until one day, a hero arrived.",
    "With a sword in one hand and a magical scroll of immense power in the other, he banished the darkness, ",
    "and established the new Kingdom of Vectors.",
    "The hero tucked the scroll away into a labyrinth, so that it would never fall into the wrong hands.",
    "Now, however, the Kingdom of Liked Lists is arising once again, and a new hero must venture to find the legendary Scroll of Digerence.",
    "That hero is you.",
    "[Press any key to continue]"
};
vector<string> WinText = {
    "Xylograth, the Being of Digerence is dead. ",
    "You have defeated him, and it is now time for you to take what you came for. ",
    "You walk up to the pedestal where the scroll awaits you, and pick it up. ",
    "With the Scroll of Digerence in hand, you make your way back to the surface, all of the barriers opening themselves before you. ",
    "With this scroll, you have the power to stop the evil that the Kingdom of Liked Lists will once again try to bring about.",
    "[Press any key to continue]"
};

int main() {
    screenManip sm;
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws); 
    int lines = ws.ws_row;
    int columns = ws.ws_col;
    if (lines < 52 || columns < 146) {
        cerr << "Terminal size not large enough to display game, please fullscreen or zoom out of the terminal before restarting." << endl;
        return 1;
    }
    mini sounds;
    bool stop = false;
    string test = "Title.wav";
    //thread music(&mini::playMenuTheme, &sounds, &stop, test.data());
    vector<string> screen;
    int max = 50;
    screen.resize(max);
    sm.clearScreen(&screen);
    for (int i = 10; i < 16; i++) {
        screen.at(i) = "                                  " + title[i-10] + "                                   ";

    }
    screen.at(30) = "                                                                 > Start game                                                                   ";
    screen.at(33) = "                                                                   Quit                                                                         ";



    sm.printScreen(&screen);

    static struct termios oldt, newt;

    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    tcgetattr( STDIN_FILENO, &oldt);
    /*now the settings will be copied*/
    newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    newt.c_lflag &= ~(ICANON);          

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    /*This is your part:
    I choose 'e' to end input. Notice that EOF is also turned off
    in the non-canonical mode*/
    char lastInput = 'w';
    //thread music(&mini::playMenuTheme, &sounds, &stop, test.data());
    int loop = 0;
    //thread music(&mini::playMenuTheme, &sounds, &stop, test.data());
    thread music2;
    do{
        if (loop == 0) {
            thread music(&mini::playMenuTheme, &sounds, &stop, test.data());
            swap(music, music2);
        }
        sm.printScreen(&screen);
        double microsecond = 1000000;
        usleep(0.03125 * microsecond);//sleeps for 3 second
        char input = getchar();

        if (input == 's') {
            screen[30][65] = ' ';
            screen[33][65] = '>';
            sm.printScreen(&screen);
            lastInput = 's';
        }
        else if (input == 'w') {
            screen[30][65] = '>';
            screen[33][65] = ' ';
            sm.printScreen(&screen);
            lastInput = 'w';
        }
        else if (input == '\n') {
            if (lastInput == 's') {
                stop = true;
                music2.join();
                //usleep(0.03125 * microsecond);
                break;
            }
            else {
                mapMovements mm;
                sm.clearScreen(&screen);
                for (int i = 0; i<IntroText.size(); i++) {
                    sm.printCenterFirstAvail(&screen, i+10, IntroText[i]);
                }
                sm.printScreen(&screen);
                char garbage = getchar();
                stop = true;
                int i = mm.gameStart(&screen);
                music2.join();
                stop = false;
                loop = 0;
                if (i == 1) {
                    sm.clearScreen(&screen);
                    for (int j = 0; j<WinText.size(); j++) {
                        sm.printCenterFirstAvail(&screen, j+10, WinText[j]);
                    }
                    sm.printScreen(&screen);
                    char garbage = getchar();
                    screen.resize(0);
                    screen.resize(50);
                    sm.clearScreen(&screen);
                    for (int j = 0; j<5; j++) {
                        sm.printCenterFirstAvail(&screen, j+10, gameWin[j]);
                    }
                    sm.printScreen(&screen);
                    return 0;
                }
                screen.resize(0);
                screen.resize(50);
                sm.clearScreen(&screen);
                for (int j = 0; j<5; j++) {
                    sm.printCenterFirstAvail(&screen, j+10, gameOver[j]);
                }
                sm.printScreen(&screen);
                //thread music2(&mini::playMenuTheme, &sounds, &stop, test.data());
                return 0;
            }
        }
        if (loop==0) {
            loop=1;
        }
        


    } while (true);
    //printLoop.join();
    /*restore the old settings*/
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    
    
    return 0;
}
