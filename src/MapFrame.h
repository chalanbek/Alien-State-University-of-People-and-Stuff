#pragma once
#include "defines.h"
#include "SDL3/SDL.h"
#include <math.h>

class MapFrame{
public:
    MapFrame();
    void setContent(MAP_FRAME_CONTENT);
    void setContent(MapFrame fullFrame);
    void setElement(int x, int y, char c);
    void draw(SDL_Renderer *renderer, SDL_Texture *mapTexture, int x, int y, bool mapMode);
    int countGsf(int x, int y, int floorNumber, playerRotation rotation);
    void countLight(int x, int y, playerRotation rotation);
    ScreenFrameName countScreenFrame(int x, int y, playerRotation rotation);
    bool checkFloorNumberKnowledge(int x, int y, playerRotation rotation);
private:
    bool isEmpty(char c);
    bool isExit(char c);
    bool isClear(char c);
    bool isPassage(char c);
    bool isFloorChange(char c);
    bool isKeyRoom(char c);
    bool isWall(char c);
    bool isWallOrDoor(char c);
    char *mapContent[MAIN_MAP_HEIGHT];
    int frameColors[MAIN_MAP_HEIGHT][MAIN_MAP_WIDTH];
};