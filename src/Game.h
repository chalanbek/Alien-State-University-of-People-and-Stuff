#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include "defines.h"    
#include "MainScreen.h"
#include "MainMap.h"
#include "TipsWindow.h"
#include "PlayerState.h"
#include "ExtraUI.h"
#include "SpawnTemplates.h"

class Game{
public:
    Game();
    ~Game();
    SDL_AppResult init(void **appstate, int argc, char *argv[]);
    SDL_AppResult processEvents(void *appstate, SDL_Event *event);
    void run();
private:
    void draw();
    void addToKcCurrent(int key);
    SDL_AppResult processRunEvents(SDL_Event *event);
    SDL_AppResult processStartEvents(SDL_Event *event);
    SDL_AppResult processEndEvents(SDL_Event *event);
    SDL_AppResult processHelpEvents(SDL_Event *event);
    SDL_AppResult processCheaterEvents(SDL_Event *event);
    SDL_AppResult processRunKeys(SDL_Event *event);
    enum GameState{
        gameStart,
        gameRun,
        gameEnd,
        gameHelp,
        gameCheater
    };
    GameState gameState = gameStart;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    MainScreen screen;
    MainMap mainMap;
    TipsWindow tipsWindow;
    PlayerState playerState;
    ExtraUI extraUI;
    int gsf;
    bool mapMode = false;
    int x = 1;
    int y = 1;
    int floorNumber = 0;
    playerRotation rotation = rotationR;
    bool isFloorKnown = false;
    ScreenFrameName currentFrameName;
    int kc[10] = {
        SDLK_UP, SDLK_UP, SDLK_DOWN, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_LEFT, SDLK_RIGHT, SDLK_B, SDLK_A
    };
    int kcCurrent[10] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
};
