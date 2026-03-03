#pragma once
#include "defines.h"
#include "SDL3/SDL.h"

class ScreenFrame
{
public:
    ScreenFrame();
    ScreenFrame(SCREEN_FRAME_CONTENT);
    void setContent(SCREEN_FRAME_CONTENT);
    void setContent(ScreenFrame frame);
    void draw(SDL_Renderer *renderer);
    void setColorNumber(int floorNumber);
private:
    char *screenContent[MAIN_SCREEN_HEIGHT];
    int colorNumber = 0;
    SDL_Color colors[FLOORS_NUMBER+1] = {
        RED_STRUCT,
        BLACK_STRUCT,
        GREY_STRUCT,
        GREEN_STRUCT,
        WHITE_STRUCT
    };
};

