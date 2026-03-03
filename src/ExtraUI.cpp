#include "ExtraUI.h"

ExtraUI::ExtraUI(){
    load();
}

ExtraUI::~ExtraUI(){
    SDL_DestroyTexture(startTexture);
    SDL_DestroyTexture(endTexture);
    SDL_DestroyTexture(helpTexture);
    SDL_UnbindAudioStream(stream);
    SDL_DestroyAudioStream(stream);
    SDL_CloseAudioDevice(device);
    SDL_free(runThemeData);
}

void ExtraUI::load(){
    try{
        std::ifstream frameFile("assets/gameEnd.txt");
        std::string frameString;
        char c;
        int currentRow = 0; 
        while (frameFile.get(c)){
            if(c == '\n'){
                gameEndFrame[currentRow] = new char[END_SCREEN_WIDTH];
                strcpy(gameEndFrame[currentRow], frameString.c_str());
                ++currentRow;
                frameString = "";
            }
            else
                frameString += c;

        }
        frameFile.close();
    }
    catch (std::exception e){
        std::cout<<e.what()<<'\n';
    }
}

void ExtraUI::init(SDL_Renderer *rendererP){
    int messageLengthC = SDL_strlen(startMessage);
    int messageLength = messageLengthC * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int messageW = messageLength * 1.5;
    int messageH = messageW/16*9;

    int messageLengthCh = SDL_strlen(cheaterMessage) * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int messageChW = messageLengthCh * 1.5;
    int messageChH = messageChW/16*9;

    int endW = END_SCREEN_WIDTH * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int endH = END_SCREEN_HEIGHT * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;

    renderer = rendererP;

    startTexture = SDL_CreateTexture(renderer, 
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, messageW, messageH);
    endTexture = SDL_CreateTexture(renderer, 
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, endW, endH);
    helpTexture = SDL_CreateTexture(renderer, 
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, HELP_SCREEN_WIDTH_P, HELP_SCREEN_HEIGHT_P);
    cheaterTexture = SDL_CreateTexture(renderer, 
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, messageChW, messageChH);

    spec.format = SDL_AUDIO_S16;
    spec.channels = 2;
    spec.freq = 48000;
    device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
    SDL_LoadWAV("assets/audio/exampleAudio.wav", &runThemeSpec, &runThemeData, &runThemeLength);

    stream = SDL_CreateAudioStream(&runThemeSpec, &spec);
    SDL_BindAudioStream(device, stream);

}

void ExtraUI::drawStartScreen(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    int messageLengthC = SDL_strlen(startMessage);
    int messageLength = messageLengthC * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int messageW = messageLength * 1.5;
    int messageH = messageW/16*9;
    int messageX = (messageW-messageLength)/2;
    int messageY = (messageH-SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE)/2;
    
    SDL_SetRenderTarget(renderer, startTexture);

    float t = SDL_GetTicks() / 1000.0f;
    for(int i=0; i < messageLengthC; ++i){
        char c[2] = {startMessage[i], '\0'};
        int x = messageX + i * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
        int y = messageY;
        int r = (int)((sin(t * 0.5 ) + 1) * 127.5);
        int g = (int)((sin(t * 0.5 + 2.0 + COLOR_PHASE*i) + 1) * 127.5);
        int b = (int)((sin(t * 0.5 + 4.0 + COLOR_PHASE*i) + 1) * 127.5);
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderDebugText(renderer, x, y, c);
    }

    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderTexture(renderer, startTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void ExtraUI::drawEndScreen(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderTarget(renderer, endTexture);
    SDL_RenderClear(renderer);
    float t = SDL_GetTicks() / 1000.0f;
    for(int i=0; i < END_SCREEN_HEIGHT; ++i){
        for(int j=0; j < END_SCREEN_WIDTH; ++j){
            char c[2] = {gameEndFrame[i][j], '\0'};
            int x = j * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
            int y = i * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
            float phase = COLOR_PHASE * (i+j) * 0.2;
            int r = (int)((sin(t * 0.5 + phase*0.9) + 1) * 127.5);
            int g = (int)((sin(t * 0.5 + 2.0 + phase) + 1) * 127.5);
            int b = (int)((sin(t * 0.5 + 4.0 + phase*1.1) + 1) * 127.5);
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);            
            SDL_RenderDebugText(renderer, x, y, c);
        }
    }

    SDL_FRect endRect = {
        0, 
        0,
        1920,
        1080
    };
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderTexture(renderer, endTexture, NULL, &endRect);
    SDL_RenderPresent(renderer);
}

void ExtraUI::drawHelpScreen(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int xOffset = 1;
    int yOffset = 1;
    int colfNum = 0;

    SDL_SetRenderTarget(renderer, helpTexture);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(int i=0; i < strlen(helpMessage); ++i){
        char c = helpMessage[i];
        if(c == '\n'){
            ++yOffset;
            xOffset = 1;
        } else
        if(c == '\t')
            xOffset += 4;
        else
        if(c == '\r')
            ++colfNum;
        else {
            int x = xOffset * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
            int y = yOffset * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * 1.8;
            
            if(colfNum > 0){
                float t = SDL_GetTicks() / 1000.0f;
                int r = (int)((sin(t * 0.5 + COLOR_PHASE*i*5) + 1) * 127.5);
                int g = (int)((sin(t * 0.5 + 2.0 + COLOR_PHASE*i*5) + 1) * 127.5);
                int b = (int)((sin(t * 0.5 + 4.0 + COLOR_PHASE*i*5) + 1) * 127.5);
                SDL_SetRenderDrawColor(renderer, r, g, b, 255);
                --colfNum;
            }
            else
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            
            char cf[2] = {c, '\0'};
            SDL_RenderDebugText(renderer, x, y, cf);
            ++xOffset;
        }
    }
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderTexture(renderer, helpTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void ExtraUI::drawCheaterScreen(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    int messageLengthC = SDL_strlen(cheaterMessage);
    int messageLength = messageLengthC * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int messageW = messageLength * 1.5;
    int messageH = messageW/16*9;
    int messageX = (messageW-messageLength)/2;
    int messageY = (messageH-SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE)/2;
    
    SDL_SetRenderTarget(renderer, cheaterTexture);

    float t = SDL_GetTicks() / 100.0f;
    for(int i=0; i < messageLengthC; ++i){
        char c[2] = {cheaterMessage[i], '\0'};
        int x = messageX + i * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
        int y = messageY;
        int r = (int)((sin(t * 0.01 )) * 77.5+177.5);
        int g = (int)((sin(t * 0.5 + 2.0 + COLOR_PHASE*i) + 1) * 127.5);
        int b = (int)((sin(t + 4.0 + COLOR_PHASE*i) + 1) * 127.5);
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderDebugText(renderer, x, y, c);
    }

    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderTexture(renderer, cheaterTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void ExtraUI::startRunTheme(){
    SDL_ClearAudioStream(stream);
    SDL_PutAudioStreamData(stream, runThemeData, runThemeLength);
}

void ExtraUI::stopRunTheme(){
    SDL_ClearAudioStream(stream);
}

bool ExtraUI::isRunThemeEnded(){
    return SDL_GetAudioStreamQueued(stream) == 0;
}