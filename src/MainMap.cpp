#include "MainMap.h"

MainMap::MainMap(int *gsfP, bool *mapModeP, int *xP, int *yP, int *floorNumberP, playerRotation *rotationP, ScreenFrameName *currentFrameNameP, bool *isFloorKnownP){
    loadFrames();
    gsf = gsfP;
    mapMode = mapModeP;
    x = xP;
    y = yP;
    floorNumber = floorNumberP;
    rotation = rotationP;
    isFloorKnown = isFloorKnownP;
    currentFrameName = currentFrameNameP;
}

void MainMap::init(SDL_Renderer *rendererP){
    renderer = rendererP;
    int mapWidth = MAIN_MAP_WIDTH * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int mapHeight = MAIN_MAP_HEIGHT * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    mapTexture = SDL_CreateTexture(renderer,
                                    SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET,
                                    mapWidth, mapHeight);
    shownFrames[*floorNumber].setContent(fullFrames[*floorNumber]);
    shownFrames[*floorNumber].setElement(*x, *y, '@');
}

void MainMap::loadFrames(){
    try{
        for(int i=0; i < FLOORS_NUMBER; ++i){
            std::ifstream frameFile("assets/mapTemplates/1/" + std::to_string(i) + ".txt");
            std::string frameString;
            char c;
            int currentRow = 0; 
            char *content[MAIN_MAP_HEIGHT];
            while (frameFile.get(c)){
                if(c == '\n'){
                    content[currentRow] = new char[MAIN_MAP_WIDTH];
                    strcpy(content[currentRow], frameString.c_str());
                    ++currentRow;
                    frameString = "";
                }
                else
                    frameString += c;

            }
            fullFrames[i].setContent(content);
            shownFrames[i].setContent(content);
            frameFile.close();
        }
    }
    catch (std::exception e){
        std::cout<<e.what()<<'\n';
    }
}

void MainMap::draw(){
    shownFrames[*floorNumber].draw(renderer, mapTexture, *x, *y, *mapMode);
}

void MainMap::movePlayer(){
    shownFrames[*floorNumber].setContent(fullFrames[*floorNumber]);
    switch (*rotation)
    {
    case rotationR:
        ++*x;
        break;
    case rotationUR:
        ++*x;
        --*y;
        break;
    case rotationU:
        --*y;
        break;
    case rotationUL:
        --*x;
        --*y;
        break;
    case rotationL:
        --*x;
        break;
    case rotationDL:
        --*x;
        ++*y;
        break;
    case rotationD:
        ++*y;
        break;
        
    case rotationDR:
        ++*x;
        ++*y;
        break;
    default:
        break;
    }
    shownFrames[*floorNumber].setElement(*x, *y, '@');
}

void MainMap::incFloorNumber(){
    if(*floorNumber < FLOORS_NUMBER - 1) ++*floorNumber;
    shownFrames[*floorNumber].setElement(*x, *y, '@');
}

void MainMap::decFloorNumber(){
    if(*floorNumber > 0) --*floorNumber;
    shownFrames[*floorNumber].setElement(*x, *y, '@');
}

void MainMap::turnRight(){
    *rotation = static_cast<playerRotation>((static_cast<int>(*rotation)+7)%8);
}

void MainMap::turnLeft(){
    *rotation = static_cast<playerRotation>((static_cast<int>(*rotation)+1)%8);
}

void MainMap::countGsf(){
    *gsf = fullFrames[*floorNumber].countGsf(*x, *y, *floorNumber, *rotation);
}

void MainMap::countLight(){
    shownFrames[*floorNumber].countLight(*x, *y, *rotation);
}

void MainMap::countScreenFrame(){
    *currentFrameName = fullFrames[*floorNumber].countScreenFrame(*x, *y, *rotation);
}

void MainMap::checkFloorNumberKnowledge(){
    if(!*isFloorKnown)
        *isFloorKnown = fullFrames[*floorNumber].checkFloorNumberKnowledge(*x, *y, *rotation);
}