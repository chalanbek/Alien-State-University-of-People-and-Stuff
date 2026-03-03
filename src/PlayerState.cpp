#include "PlayerState.h"
#include <iostream>

PlayerState::PlayerState(bool *mapModeP, int *floorNumberP, playerRotation *rotationP, bool *isFloorKnownP){
    mapMode = mapModeP;
    floorNumber = floorNumberP;
    rotation = rotationP;
    isFloorKnown = isFloorKnownP;
    loadFrames();
}

void PlayerState::init(SDL_Renderer *rendererP){
    renderer = rendererP;
    int psWidth = PLAYER_STATE_WIDTH * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int psHeight = PLAYER_STATE_HEIGHT * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int arrowWidth = ARROW_SIZE * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int arrowHeight = ARROW_SIZE * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int flrTextWidth = SDL_strlen(floorText) * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int flrTextHeight = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    playerState = SDL_CreateTexture(renderer,
                                    SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET,
                                    psWidth, psHeight);
    arrow = SDL_CreateTexture(renderer,
                                    SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET,
                                    arrowWidth, arrowHeight);
    floorTextTexture = SDL_CreateTexture(renderer,
                                    SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET,
                                    flrTextWidth, flrTextHeight);
}

void PlayerState::draw(){
    if(*isFloorKnown)
        asprintf(&floorText, "Current floor: %d", *floorNumber);
        
    else 
        floorText = "Current floor: N/A";
    
    int psWidth = PLAYER_STATE_WIDTH * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int psHeight = PLAYER_STATE_HEIGHT * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int arrowShownWidth = ARROW_SHOWN_SIZE * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int arrowShownHeight = ARROW_SHOWN_SIZE * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int flrTextWidth = SDL_strlen(floorText) * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int flrTextHeight = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int flrTextPosX = arrowShownWidth;
    int flrTextPosY = (ARROW_SHOWN_SIZE/2) * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int flrTextShownWidth = MAIN_MAP_WIDTH * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE - flrTextPosX;
    int flrTextShownHeight = flrTextShownWidth / flrTextWidth * flrTextHeight;

    SDL_SetRenderTarget(renderer, arrow);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int i=0; i < ARROW_SIZE; ++i)
        for(int j=0; j < ARROW_SIZE; ++j){
            float x = j * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
            float y = i * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
            char c[2] = {arrows[static_cast<int>(*rotation)][i][j], '\0'};
            SDL_RenderDebugText(renderer, x, y, c);
        }
    SDL_SetRenderTarget(renderer, playerState);
    SDL_FRect arrowRect ={
        0,
        0,
        arrowShownWidth,
        arrowShownHeight
    };
    SDL_RenderTexture(renderer, arrow, NULL, &arrowRect);

    SDL_SetRenderTarget(renderer, floorTextTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, 0, 0, floorText);
    SDL_SetRenderTarget(renderer, playerState);
    SDL_FRect floorRect = {
        flrTextPosX,
        flrTextPosY,
        flrTextShownWidth,
        flrTextShownHeight
    };
    SDL_RenderTexture(renderer, floorTextTexture, NULL, &floorRect);

    SDL_SetRenderTarget(renderer, NULL);
    SDL_FRect dstRect = {
        PLAYER_STATE_POS_X,
        PLAYER_STATE_POS_Y,
        psWidth,
        psHeight
    };
    if(*mapMode)
        SDL_SetTextureAlphaMod(playerState, 75);
    else
        SDL_SetTextureAlphaMod(playerState, 255);
    SDL_RenderTexture(renderer, playerState, NULL, &dstRect);
}

void PlayerState::loadFrames(){
    try{
        for(int i=0; i < 8; ++i){
            std::ifstream frameFile("assets/playerState/arrows/" + std::to_string(i) + ".txt");
            std::string frameString;
            char c;
            int currentRow = 0; 
            while (frameFile.get(c)){
                if(c == '\n'){
                    arrows[i][currentRow] = new char[5];
                    strcpy(arrows[i][currentRow], frameString.c_str());
                    ++currentRow;
                    frameString = "";
                }
                else
                    frameString += c;

            }
        }
    }
    catch (std::exception e){
        std::cout<<e.what()<<'\n';
    }
}