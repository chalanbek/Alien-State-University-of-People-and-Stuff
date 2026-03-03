#include "TipsWindow.h"

TipsWindow::TipsWindow(int *gsfP){
    gsf = gsfP;
}

void TipsWindow::init(SDL_Renderer *rendererP){
    renderer = rendererP;
    int windowW = TIP_MAX_WIDTH * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int windowH = windowW*TIPS_WINDOW_HEIGHT/TIPS_WINDOW_WIDTH;
    tipsWindow = SDL_CreateTexture(renderer, 
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowW, windowH);
}

void TipsWindow::draw(){
    int yOffset = 0;
    
    SDL_SetRenderTarget(renderer, tipsWindow);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if(*gsf & GSF_CAN_EXIT){
        SDL_RenderDebugText(renderer, 0, yOffset, "press C to exit!");
        yOffset += 2 * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    }
    if(*gsf & GSF_CAN_MOVE){
        SDL_RenderDebugText(renderer, 0, yOffset, "press I to move forward");
        yOffset += 2 * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    }
    if(*gsf & GSF_CAN_ROTATE){
        SDL_RenderDebugText(renderer, 0, yOffset, "press J or L to rotate <- ->");
        yOffset += 2 * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    }
    if(*gsf & GSF_CAN_GO_UP){
        SDL_RenderDebugText(renderer, 0, yOffset, "press Z to go up");
        yOffset += 2 * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    }
    if(*gsf & GSF_CAN_GO_DOWN){
        SDL_RenderDebugText(renderer, 0, yOffset, "press X to go down");
        yOffset += 2 * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    }


    SDL_SetRenderTarget(renderer, NULL);
    SDL_FRect dstRect = {
        TIPS_WINDOW_POS_X,
        TIPS_WINDOW_POS_Y,
        TIPS_WINDOW_WIDTH * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE,
        TIPS_WINDOW_HEIGHT * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE
    };
    SDL_RenderTexture(renderer, tipsWindow, NULL, &dstRect);
}