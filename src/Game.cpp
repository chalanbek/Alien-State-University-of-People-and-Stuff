#include "Game.h"

Game::Game():
screen(&floorNumber, &currentFrameName, &isFloorKnown),
mainMap(&gsf, &mapMode, &x, &y, &floorNumber, &rotation, &currentFrameName, &isFloorKnown),
playerState(&mapMode, &floorNumber, &rotation, &isFloorKnown),
tipsWindow(&gsf){
}

Game::~Game(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

SDL_AppResult Game::init(void **appstate, int argc, char *argv[]){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (!SDL_CreateWindowAndRenderer(WINDOW_NAME, 800, 600, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SpawnTemplates::chooseTemplate(&floorNumber, &x, &y);
    
    screen.init(renderer);
    mainMap.init(renderer);
    playerState.init(renderer);
    tipsWindow.init(renderer);
    extraUI.init(renderer);

    mainMap.countScreenFrame();
    screen.changeColor();
    return SDL_APP_CONTINUE;
}

SDL_AppResult Game::processEvents(void *appstate, SDL_Event *event){
    switch (gameState)
    {
    case gameStart:
        return processStartEvents(event);
        break;
    case gameRun:
        return processRunEvents(event);
        break;
    case gameEnd:
        return processEndEvents(event);
        break;
    case gameHelp:
        return processHelpEvents(event);
        break;
    case gameCheater:
        return processCheaterEvents(event);
        break;
    default:
        return SDL_APP_CONTINUE;
        break;
    }
}

void Game::run(){
    switch (gameState)
    {
    case gameStart:
        extraUI.drawStartScreen();
        break;
    case gameRun:
        if(extraUI.isRunThemeEnded())
            extraUI.startRunTheme();
        draw();
        break;
    case gameEnd:
        extraUI.drawEndScreen();
        break;
    case gameHelp:
        if(extraUI.isRunThemeEnded())
                extraUI.startRunTheme();
        extraUI.drawHelpScreen();
        break;
    case gameCheater:
        extraUI.drawCheaterScreen();
        break;
    default:
        break;
    }
}

void Game::draw(){
    mainMap.countGsf();
    mainMap.countLight();
    mainMap.countScreenFrame();
    mainMap.checkFloorNumberKnowledge();
    screen.changeColor();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    mainMap.draw();
    playerState.draw();
    if(!mapMode){
        screen.draw();
        tipsWindow.draw();
    }
    SDL_RenderPresent(renderer);
}

SDL_AppResult Game::processRunEvents(SDL_Event *event){
    switch (event->type)
    {
    case SDL_EVENT_KEY_DOWN:
        return processRunKeys(event);
        break;
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;
    default:
        return SDL_APP_CONTINUE;
        break;
    }
}

SDL_AppResult Game::processStartEvents(SDL_Event *event){
    switch (event->type)
    {
    case SDL_EVENT_KEY_DOWN:
        gameState = gameRun;
        extraUI.startRunTheme();
        return SDL_APP_CONTINUE;
        break;
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;
    default:
        return SDL_APP_CONTINUE;
        break;
    }
}

SDL_AppResult Game::processEndEvents(SDL_Event *event){
    switch (event->type)
    {
    case SDL_EVENT_KEY_DOWN:
        return SDL_APP_SUCCESS;
        break;
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;
    default:
        return SDL_APP_CONTINUE;
        break;
    }
}

SDL_AppResult Game::processHelpEvents(SDL_Event *event){
    switch (event->type)
    {
    case SDL_EVENT_KEY_DOWN:
        gameState = gameRun;
        return SDL_APP_CONTINUE;
        break;
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;
    default:
        return SDL_APP_CONTINUE;
        break;
    }
}

SDL_AppResult Game::processCheaterEvents(SDL_Event *event){
    switch (event->type)
    {
    case SDL_EVENT_KEY_DOWN:
        gameState = gameEnd;
        return SDL_APP_CONTINUE;
        break;
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;
    default:
        return SDL_APP_CONTINUE;
        break;
    }
}


SDL_AppResult Game::processRunKeys(SDL_Event *event){
    addToKcCurrent(event->key.key);
    int i=0;
    for(i=0; i < 10; ++i)
        if(kc[i] != kcCurrent[i]) break;
    if(i==10){
        extraUI.stopRunTheme();
        gameState = gameCheater;
        return SDL_APP_CONTINUE;
    }
    switch (event->key.key)
    {
    case SDLK_F1:
        gameState = gameHelp;
        break;
    case SDLK_I:
        if(gsf & GSF_CAN_MOVE)
            mainMap.movePlayer();
        break;
    case SDLK_J:
        if(gsf & GSF_CAN_ROTATE){
            mainMap.turnLeft();
        }
            
        break;
    case SDLK_L:
        if(gsf & GSF_CAN_ROTATE){
            mainMap.turnRight();
        }
        break;
    case SDLK_Z:
        if(gsf & GSF_CAN_GO_UP){
            mainMap.incFloorNumber();
            screen.changeColor();
        }
        break;
    case SDLK_X:
        if(gsf & GSF_CAN_GO_DOWN){
            mainMap.decFloorNumber();
            screen.changeColor();
        }   
        break;
    case SDLK_C:
        if(gsf & GSF_CAN_EXIT){
            extraUI.stopRunTheme();
            gameState = gameEnd;
        }
        break;
    case SDLK_M:
        mapMode = !mapMode;
        break;
    default:
        break;
    }
    return SDL_APP_CONTINUE;
}

void Game::addToKcCurrent(int key){
    for(int i=0; i < 9; ++i)
      kcCurrent[i] = kcCurrent[i+1];
    kcCurrent[9] = key;
}
