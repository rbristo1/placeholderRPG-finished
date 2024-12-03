#define MINIAUDIO_IMPLEMENTATION
#include "miniAudioSounds.h"
#include <stdio.h>
#include <unistd.h>
#include <chrono>
#include <thread>
using namespace std;
void mini::playMenuTheme(bool * stop, char * filename)
{
    ma_result result;
    ma_engine engine;
    ma_sound sound;

    ma_sound_set_fade_in_milliseconds(&sound, 0, 1, 1000);

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        return;
    }
    //ma_engine_play_sound(&engine, filename, NULL);
    result = ma_sound_init_from_file(&engine, filename, 0, NULL, NULL, &sound);
    ma_sound_start(&sound);
    ma_sound_set_looping(&sound, true);
    //ma_sound_set_fade_in_milliseconds(&sound, -1, 0, 1000);

    //double microsecond = 1000000;
    //sleep_until(system_clock::now() + seconds(300));
    while (true) {
        if (*stop == true) {
            ma_sound_set_fade_in_milliseconds(&sound, -1, 0, 1000);
            usleep(1 * 1000000);
            ma_engine_uninit(&engine);
            return;
        }
    }
    

    return;
}
void mini::playBossTheme(bool * stop, char * filename, char * filename2)
{

   /* ma_result result;
    ma_engine engine;
    ma_sound sound;

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        return;
    }
    //ma_engine_play_sound(&engine, filename, NULL);
    result = ma_sound_init_from_file(&engine, filename, 0, NULL, NULL, &sound);
    ma_sound_start(&sound);
    //ma_sound_set_fade_in_milliseconds(&sound, -1, 0, 1000);

    //double microsecond = 1000000;
    //sleep_until(system_clock::now() + seconds(300));
    while (!ma_sound_at_end(&sound)) {
        if (*stop == true) {
            ma_sound_set_fade_in_milliseconds(&sound, -1, 0, 1000);
            usleep(1 * 1000000);
            ma_engine_uninit(&engine);
            return;
        }
    }
    ma_result result2;
    ma_engine engine2;
    ma_sound sound2;
    result2 = ma_sound_init_from_file(&engine, filename2, 0, NULL, NULL, &sound2);
    ma_sound_start(&sound2);
    ma_sound_set_looping(&sound2, true);
    while (true) {
        if (*stop == true) {
            ma_sound_set_fade_in_milliseconds(&sound2, -1, 0, 1000);
            usleep(1 * 1000000);
            ma_engine_uninit(&engine);
            ma_engine_uninit(&engine2);
            return;
        }
    }


    ma_engine_uninit(&engine);
    ma_engine_uninit(&engine2);
    return;*/
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