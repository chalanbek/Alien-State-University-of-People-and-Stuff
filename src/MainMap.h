#pragma once
#include "MapFrame.h"
#include "SDL3/SDL.h"
#include "fstream"
#include "iostream"

class MainMap{
public:
    MainMap(int *gsfP, bool *mapModeP, int *xP, int *yP, int *floorNumberP, playerRotation *rotationP, ScreenFrameName *currentFrameNameP, bool *isFloorKnownP);
    void init(SDL_Renderer *rendererP);
    void draw();
    void movePlayer();
    void incFloorNumber();
    void decFloorNumber();
    void turnRight();
    void turnLeft();
    void countGsf();
    void countLight();
    void countScreenFrame();
    void checkFloorNumberKnowledge();
private:
    void loadFrames();
    MapFrame fullFrames[FLOORS_NUMBER];
    MapFrame shownFrames[FLOORS_NUMBER];
    SDL_Texture *mapTexture;
    SDL_Renderer *renderer;
    int *gsf;
    bool *mapMode;
    int *x;
    int *y;
    int *floorNumber;
    playerRotation *rotation;
    bool *isFloorKnown;
    ScreenFrameName *currentFrameName;
};