#include "ScreenFrame.h"
ScreenFrame::ScreenFrame(){
    for(int i=0; i < MAIN_SCREEN_HEIGHT; ++i){
        screenContent[i] = "";
    }
}

ScreenFrame::ScreenFrame(SCREEN_FRAME_CONTENT){
    for(int i=0; i < MAIN_SCREEN_HEIGHT; ++i){
        screenContent[i] = new char[MAIN_SCREEN_WIDTH];
        strcpy(screenContent[i], content[i]);
    }
}

void ScreenFrame::setContent(SCREEN_FRAME_CONTENT){
    for(int i=0; i < MAIN_SCREEN_HEIGHT; ++i){
        screenContent[i] = new char[MAIN_SCREEN_WIDTH];
        strcpy(screenContent[i], content[i]);
    }
}

void ScreenFrame::setContent(ScreenFrame frame){
    setContent(frame.screenContent);
}

void ScreenFrame::draw(SDL_Renderer *renderer){
    for(int i=0; i < MAIN_SCREEN_HEIGHT; ++i){
        float x = SCREEN_POS_X;
        float y = SCREEN_POS_Y + SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * i;
        SDL_Color currentColor = colors[colorNumber];
        SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
        SDL_RenderDebugText(renderer, x, y, screenContent[i]);
    }
}

void ScreenFrame::setColorNumber(int floorNumber){
    colorNumber = floorNumber;
}