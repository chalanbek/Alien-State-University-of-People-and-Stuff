#pragma once
#include "defines.h"
#include "SDL3/SDL.h"

class TipsWindow
{
public:
    TipsWindow(int *gsfP);
    void init(SDL_Renderer *renderer);
    void draw();
private:
    SDL_Renderer *renderer;
    SDL_Texture *tipsWindow;
    int *gsf;
};
