

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
//vectors containing the title screen, game over screen, and game win screen.

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

//holds the text displayed at the very beginning and end of the game
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
    //used to output things to the screen
    screenManip sm;

    //finds terminal window size based on linux environment variables
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws); 

    //terminal length and width
    int lines = ws.ws_row;
    int columns = ws.ws_col;

    //if terminal is too small for the game to be displayed, it outputs an error message to the user and quits
    if (lines < 52 || columns < 146) {
        cerr << "Terminal size not large enough to display game, please fullscreen or zoom out of the terminal before restarting." << endl;
        return 1;
    }

    //title screen music helpers
    mini sounds;
    bool stop = false;
    string test = "Title.wav";

    //initializes screen vector (50 tall, 144 wide) with main menu text
    vector<string> screen;
    int max = 50;
    screen.resize(max);
    sm.clearScreen(&screen);
    for (int i = 10; i < 16; i++) {
        screen.at(i) = "                                  " + title[i-10] + "                                   ";

    }
    screen.at(30) = "                                                                 > Start game                                                                   ";
    screen.at(33) = "                                                                   Quit                                                                         ";


    //forbidden stack overflow knowledge:
    //https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar-for-reading-a-single-character-only
    //allows for a character input to be read without needing to press the newline key
    static struct termios oldt, newt;

    //gets parameters of the current terminal
    tcgetattr( STDIN_FILENO, &oldt);
    //copies them to new terminal
    newt = oldt;

    //ICANON normally takes care that one line at a time, so it is inverted
    newt.c_lflag &= ~(ICANON);          

    //new settings are sent to STDIN and attributes are changed immediately
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
    
    char lastInput = 'w';

    //checks if music needs to be restarted
    int loop = 0;

    //global music thread
    thread music2;
    do{
        if (loop == 0) {

            //starts the Title music, .data() converts string to char *
            thread music(&mini::playMenuTheme, &sounds, &stop, test.data());

            //swaps local thread with global thread so it can be join()ed later.
            swap(music, music2);
        }

        //prints the finished title screen
        sm.printScreen(&screen);
        double microsecond = 1000000;

        //delays user input by 1/32 of a second
        usleep(0.03125 * microsecond);

        //recieves user char input without newline key
        char input = getchar();

        //move title screen selector down
        if (input == 's') {
            screen[30][65] = ' ';
            screen[33][65] = '>';
            sm.printScreen(&screen);
            lastInput = 's';
        }
        //move up
        else if (input == 'w') {
            screen[30][65] = '>';
            screen[33][65] = ' ';
            sm.printScreen(&screen);
            lastInput = 'w';
        }
        //select option
        else if (input == '\n') {
            //quit
            if (lastInput == 's') {
                stop = true;
                music2.join();
                break;
            }
            //start game
            else {

                //map initialize
                mapMovements mm;

                //clears screen for opening text scroll
                sm.clearScreen(&screen);

                //prints opening text scroll
                for (int i = 0; i<IntroText.size(); i++) {
                    sm.printCenterFirstAvail(&screen, i+10, IntroText[i]);
                }
                sm.printScreen(&screen);

                //wait for user input to move on
                char garbage = getchar();

                //title music stops, game starts
                stop = true;
                int i = mm.gameStart(&screen);

                //makes sure music has fully stopped, then sets the loop to 0 so it can restart if the player died
                music2.join();
                stop = false;
                loop = 0;

                //1 indicates a game win
                if (i == 1) {
                    //prints win text scroll, then game win screen, then quits
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
                    break;
                }
                //prints game over screen
                screen.resize(0);
                screen.resize(50);
                sm.clearScreen(&screen);
                for (int j = 0; j<5; j++) {
                    sm.printCenterFirstAvail(&screen, j+10, gameOver[j]);
                }
                sm.printScreen(&screen);
                //thread music2(&mini::playMenuTheme, &sounds, &stop, test.data());
                break;
            }
        }
        //sets loop to 1 so music doesnt start twice
        if (loop==0) {
            loop=1;
        }
        


    } while (true);

    //restores old settings before quitting
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    
    
    return 0;
}
