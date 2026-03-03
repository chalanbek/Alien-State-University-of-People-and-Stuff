#pragma once
#include "SDL3/SDL.h"
#include "defines.h"
#include "fstream"
#include "iostream"

class PlayerState
{
public:
    PlayerState(bool *mapModeP, int *floorNumberP, playerRotation *rotationP, bool *isFloorKnownP);
    void draw();
    void init(SDL_Renderer *rendererP);
private:
    void loadFrames();
    char *floorText = "Current floor: N/A";
    playerRotation *rotation;
    bool *mapMode;
    int *floorNumber;
    char *arrows[8][ARROW_SIZE];
    SDL_Renderer *renderer;
    SDL_Texture *playerState;
    SDL_Texture *arrow;
    SDL_Texture *floorTextTexture;
    bool *isFloorKnown;
};
