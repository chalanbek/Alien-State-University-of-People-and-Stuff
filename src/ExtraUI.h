#pragma once
#include <SDL3/SDL.h>
#include <fstream>
#include <math.h>
#include <iostream>
#include "defines.h"

class ExtraUI
{
public:
    ExtraUI();
    ~ExtraUI();
    void load();
    void init(SDL_Renderer *rendererP);
    void drawStartScreen();
    void drawEndScreen();
    void drawHelpScreen();
    void drawCheaterScreen();
    void startRunTheme();
    bool isRunThemeEnded();
    void stopRunTheme();
private:
    const char *startMessage = "Press any key to start!";
    const char *cheaterMessage = "Come on, it's not such a difficult game...";
    const char *helpMessage = "A little information about the game.\n"
    "(Press any key to exit)\n\n"

    "There is a map in the upper right corner. It opens as you explore.\n"
    "You can press M to open the map in full screen.\n"
    "Everything is represented by the following symbols:\n"
    "\t* \r@ for player;\n"
    "\t* #, |, \\, /, -, _, + for walls;\n"
    "\t* =, e for elevator / stairs;\n"
    "\t* ., ', \" for special rooms;\n"
    "\t* 0 for exit.\n\n"


    "In the upper left window you can see the tips.\n"
    "The main actions you can do are:\n"
    "\t* Press J or L to rotate on 45 degrees;\n"
    "\t* Press I to move in the current direction (if there is no wall in front);\n"
    "\t* If you are in an elevator or on the stairs, press Z or X to change floors;\n"
    "\t* If you reach the exit, press C (even if the key is broken).\n\n"

    "At the bottom left are schematic representations of what you see.\n"
    "All images are either made by \r\r\r\rewoe or taken from the internet.\n\n"

    "In the lower right corner you can see your current states.\n"
    "At the moment there is only the current direction and floor number.\n\n"

    "Please don't be a cheater!\n\n"

    "The game will continue to be developed.\n"
    "There are plans to add a lot of things (at least more than there are now).\n"
    "The game is by \r\r\r\rewoe (aka \r\r\r\r\r\r\r\r\r\rchalandbek), all questions should be directed to him.\n\n"
    ;
    SDL_Renderer *renderer;
    SDL_Texture *startTexture;
    SDL_Texture *endTexture;
    SDL_Texture *helpTexture;
    SDL_Texture *cheaterTexture;
    char *gameEndFrame[END_SCREEN_HEIGHT];
    SDL_AudioDeviceID device;
    SDL_AudioStream *stream;
    SDL_AudioSpec spec;
    SDL_AudioSpec runThemeSpec;
    Uint8 *runThemeData;
    Uint32 runThemeLength;
};

