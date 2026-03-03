#pragma once
#include "ScreenFrame.h"
#include "SDL3/SDL.h"
#include <iostream>
#include <string>
#include <fstream>

class MainScreen{
public:
    MainScreen(int *floorNumberP, ScreenFrameName *currentFrameNameP, bool *isFloorKnownP);
    void init(SDL_Renderer *rendererP);
    void draw();
    void changeColor();
private:
    void loadFrames();
    ScreenFrame frames[SCREEN_FRAMES_COUNT];
    SDL_Renderer *renderer;
    int *floorNumber;
    bool *isFloorKnown;
    ScreenFrameName *currentFrameName;
};
