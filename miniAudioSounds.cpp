#define MINIAUDIO_IMPLEMENTATION
#include "miniAudioSounds.h"
#include <stdio.h>
#include <unistd.h>
#include <chrono>
#include <thread>
using namespace std;
void mini::playMenuTheme(bool * stop, char * filename)
{
    //plays a sound file and fades out when it is stopped
    ma_result result;
    ma_engine engine;
    ma_sound sound;

    //sets fade in
    ma_sound_set_fade_in_milliseconds(&sound, 0, 1, 1000);

    result = ma_engine_init(NULL, &engine);
    //makes sure the initialization was successful
    if (result != MA_SUCCESS) {
        return;
    }
    //initializes a ma_sound from a file
    result = ma_sound_init_from_file(&engine, filename, 0, NULL, NULL, &sound);
    //starts the sound
    ma_sound_start(&sound);
    //tells it to loop
    ma_sound_set_looping(&sound, true);

    while (true) {
        if (*stop == true) {
            //sets fade out
            ma_sound_set_fade_in_milliseconds(&sound, -1, 0, 1000);
            //wait 1 sec
            usleep(1 * 1000000);
            //uinitialize
            ma_engine_uninit(&engine);
            //quit
            return;
        }
    }
    

    return;
}
void mini::playBossTheme(bool * stop, char * filename, char * filename2)
{
    //plays the boss into and then the boss main loop
    mini sounds;
    bool stop2;
    thread music2(&mini::playMenuTheme, &sounds, &stop2, filename);
    usleep(15*1000000);
    stop2 = true;
    music2.join();
    thread music3(&mini::playMenuTheme, &sounds, stop, filename2);
    music3.join();
    return;
}