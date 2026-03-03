#include "MapFrame.h"
#include <string>
#include <iostream>
#include <algorithm>

MapFrame::MapFrame(){
    for(int i=0; i < MAIN_MAP_HEIGHT; ++i){
        mapContent[i] = "";
    }
    for(int i=0;i < MAIN_MAP_HEIGHT;++i){
        std::string c = "";
        for(int j=0;j < MAIN_MAP_WIDTH;++j)
            c += '#';
        mapContent[i] = new char[MAIN_MAP_WIDTH];
        strcpy(mapContent[i], c.c_str());
    }
    for(int i=0; i < MAIN_MAP_HEIGHT; ++i)
        for(int j=0; j < MAIN_MAP_WIDTH; ++j){
            if(i == 0 || i == MAIN_MAP_HEIGHT - 1
            || j == 0 || j == MAIN_MAP_WIDTH - 1)
                frameColors[i][j] = 255;
            else
                frameColors[i][j] = 0;            
        }
}

void MapFrame::setContent(MAP_FRAME_CONTENT){
    for(int i=0; i < MAIN_MAP_HEIGHT; ++i){
        mapContent[i] = new char[MAIN_MAP_WIDTH];
        strcpy(mapContent[i], content[i]);
    }
}

void MapFrame::setContent(MapFrame fullFrame){
    setContent(fullFrame.mapContent);
}

void MapFrame::setElement(int x, int y, char c){
    if(x > 0 && x < MAIN_MAP_WIDTH - 1 && y > 0 && y< MAIN_MAP_HEIGHT - 1)
        mapContent[y][x] = c;
}

void MapFrame::draw(SDL_Renderer *renderer, SDL_Texture *mapTexture, int x, int y, bool mapMode){
    int mapWidth = MAIN_MAP_WIDTH * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    int mapHeight = MAIN_MAP_HEIGHT * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    SDL_SetRenderTarget(renderer, mapTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for(int i=0; i < MAIN_MAP_HEIGHT; ++i){
        for(int j=0; j < MAIN_MAP_WIDTH; ++j){
            uint8_t color = frameColors[i][j];
            if(j==x && i==y){
                float t = SDL_GetTicks() / 1000.0f;
                int r = (int)((sin(t * 0.5) + 1) * 127.5);
                int g = (int)((sin(t * 0.5 + 2.0 + COLOR_PHASE*i) + 1) * 127.5);
                int b = (int)((sin(t * 0.5 + 4.0 + COLOR_PHASE*i) + 1) * 127.5);
                SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            }
            else
                SDL_SetRenderDrawColor(renderer, color, color, color, 255);
            
            float x = j * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
            float y = i * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
            
            char c[1] = {mapContent[i][j]};
            SDL_RenderDebugText(renderer, x, y, c);
        }
    }
    SDL_SetRenderTarget(renderer, NULL);
    SDL_FRect dstRect = {
        MAP_POS_X,
        MAP_POS_Y,
        mapWidth,
        mapHeight
    };
    if(mapMode)
        SDL_RenderTexture(renderer, mapTexture, NULL, NULL);
    else
        SDL_RenderTexture(renderer, mapTexture, NULL, &dstRect);
}

int MapFrame::countGsf(int x, int y, int floorNumber, playerRotation rotation){
    int gsf = 0;
    gsf |= GSF_CAN_ROTATE;

    char cc = mapContent[y][x];
    char cells[8] = {
        mapContent[y][x+1],
        mapContent[y-1][x+1],
        mapContent[y-1][x],
        mapContent[y-1][x-1],
        mapContent[y][x-1],
        mapContent[y+1][x-1],
        mapContent[y+1][x],
        mapContent[y+1][x+1]
    };

    if(isFloorChange(cc)){
        if(floorNumber != 0)
            gsf |= GSF_CAN_GO_DOWN;
        if(floorNumber != FLOORS_NUMBER - 1)
            gsf |= GSF_CAN_GO_UP;
    }

    if(isExit(cc))
        gsf |= GSF_CAN_EXIT;

    
    if(isClear(cells[(static_cast<int>(rotation)+8)%8]))
        gsf |= GSF_CAN_MOVE;
 
    return gsf;
}

void MapFrame::countLight(int x, int y, playerRotation rotation){
    switch (rotation)
    {
    case rotationR:
        frameColors[y+1][x] = std::max(frameColors[y+1][x], 150);
        frameColors[y][x] = std::max(frameColors[y][x], 150);
        frameColors[y-1][x] = std::max(frameColors[y-1][x], 150);
        
        frameColors[y+1][x+1] = std::max(frameColors[y+1][x+1], 100);
        frameColors[y][x+1] = std::max(frameColors[y][x+1], 100);
        frameColors[y-1][x+1] = std::max(frameColors[y-1][x+1], 100);
        
        if(x+2 < MAIN_MAP_WIDTH) {
            frameColors[y+1][x+2] = std::max(frameColors[y+1][x+2], 50);
            frameColors[y][x+2] = std::max(frameColors[y][x+2], 50);
            frameColors[y-1][x+2] = std::max(frameColors[y-1][x+2], 50);
        }
        break;
    case rotationUR:
        frameColors[y-1][x-1] = std::max(frameColors[y-1][x-1], 150);
        frameColors[y][x] = std::max(frameColors[y][x], 150);
        frameColors[y+1][x+1] = std::max(frameColors[y+1][x+1], 150);

        frameColors[y-1][x] = std::max(frameColors[y-1][x], 100);
        frameColors[y][x+1] = std::max(frameColors[y][x+1], 100);

        frameColors[y-1][x+1] = std::max(frameColors[y-1][x+1], 50);
        if(x+2 < MAIN_MAP_WIDTH){
            frameColors[y][x+2] = std::max(frameColors[y][x+2], 50);
            frameColors[y-1][x+2] = std::max(frameColors[y-1][x+2], 50);
        }
        if(y-2 >= 0){
            frameColors[y-2][x] = std::max(frameColors[y-2][x], 50);
            frameColors[y-2][x+1] = std::max(frameColors[y-2][x+1], 50);
        }
        break;
        
    case rotationU:
        frameColors[y][x-1] = std::max(frameColors[y][x-1], 150);
        frameColors[y][x] = std::max(frameColors[y][x], 150);
        frameColors[y][x+1] = std::max(frameColors[y][x+1], 150);
        
        frameColors[y-1][x-1] = std::max(frameColors[y-1][x-1], 100);
        frameColors[y-1][x] = std::max(frameColors[y-1][x], 100);
        frameColors[y-1][x+1] = std::max(frameColors[y-1][x+1], 100);
        
        if(y-2 >= 0) {
            frameColors[y-2][x-1] = std::max(frameColors[y-2][x-1], 50);
            frameColors[y-2][x] = std::max(frameColors[y-2][x], 50);
            frameColors[y-2][x+1] = std::max(frameColors[y-2][x+1], 50);
        }
        break;

        case rotationUL:
        frameColors[y-1][x+1] = std::max(frameColors[y-1][x+1], 150);
        frameColors[y][x] = std::max(frameColors[y][x], 150);
        frameColors[y+1][x-1] = std::max(frameColors[y+1][x-1], 150);

        frameColors[y-1][x] = std::max(frameColors[y-1][x], 100);
        frameColors[y][x-1] = std::max(frameColors[y][x-1], 100);

        frameColors[y-1][x-1] = std::max(frameColors[y-1][x-1], 50);
        
        if(x-2 >= 0){
            frameColors[y][x-2] = std::max(frameColors[y][x-2], 50);
            frameColors[y-1][x-2] = std::max(frameColors[y-1][x-2], 50);
        }
        if(y-2 >= 0){
            frameColors[y-2][x] = std::max(frameColors[y-2][x], 50);
            frameColors[y-2][x-1] = std::max(frameColors[y-2][x-1], 50);
        }
        break;
        
    case rotationL:
        frameColors[y+1][x] = std::max(frameColors[y+1][x], 150);
        frameColors[y][x] = std::max(frameColors[y][x], 150);
        frameColors[y-1][x] = std::max(frameColors[y-1][x], 150);
        
        frameColors[y+1][x-1] = std::max(frameColors[y+1][x-1], 100);
        frameColors[y][x-1] = std::max(frameColors[y][x-1], 100);
        frameColors[y-1][x-1] = std::max(frameColors[y-1][x-1], 100);
        
        if(x-2 >= 0) {
            frameColors[y+1][x-2] = std::max(frameColors[y+1][x-2], 50);
            frameColors[y][x-2] = std::max(frameColors[y][x-2], 50);
            frameColors[y-1][x-2] = std::max(frameColors[y-1][x-2], 50);
        }
        break;

    case rotationDL:
        frameColors[y+1][x+1] = std::max(frameColors[y+1][x+1], 150);
        frameColors[y][x] = std::max(frameColors[y][x], 150);
        frameColors[y-1][x-1] = std::max(frameColors[y-1][x-1], 150);

        frameColors[y+1][x] = std::max(frameColors[y+1][x], 100);
        frameColors[y][x-1] = std::max(frameColors[y][x-1], 100);

        frameColors[y+1][x-1] = std::max(frameColors[y+1][x-1], 50);
        
        if(x-2 >= 0){
            frameColors[y][x-2] = std::max(frameColors[y][x-2], 50);
            frameColors[y+1][x-2] = std::max(frameColors[y+1][x-2], 50);
        }
        if(y+2 < MAIN_MAP_HEIGHT){
            frameColors[y+2][x] = std::max(frameColors[y+2][x], 50);
            frameColors[y+2][x-1] = std::max(frameColors[y+2][x-1], 50);
        }
        break;
        
    case rotationD:
        frameColors[y][x-1] = std::max(frameColors[y][x-1], 150);
        frameColors[y][x] = std::max(frameColors[y][x], 150);
        frameColors[y][x+1] = std::max(frameColors[y][x+1], 150);
        
        frameColors[y+1][x-1] = std::max(frameColors[y+1][x-1], 100);
        frameColors[y+1][x] = std::max(frameColors[y+1][x], 100);
        frameColors[y+1][x+1] = std::max(frameColors[y+1][x+1], 100);
        
        if(y+2 < MAIN_MAP_HEIGHT) {
            frameColors[y+2][x-1] = std::max(frameColors[y+2][x-1], 50);
            frameColors[y+2][x] = std::max(frameColors[y+2][x], 50);
            frameColors[y+2][x+1] = std::max(frameColors[y+2][x+1], 50);
        }
        break;

        case rotationDR:
        frameColors[y+1][x-1] = std::max(frameColors[y+1][x-1], 150);
        frameColors[y][x] = std::max(frameColors[y][x], 150);
        frameColors[y-1][x+1] = std::max(frameColors[y-1][x+1], 150);

        frameColors[y+1][x] = std::max(frameColors[y+1][x], 100);
        frameColors[y][x+1] = std::max(frameColors[y][x+1], 100);

        frameColors[y+1][x+1] = std::max(frameColors[y+1][x+1], 50);
        
        if(x+2 < MAIN_MAP_WIDTH){
            frameColors[y][x+2] = std::max(frameColors[y][x+2], 50);
            frameColors[y+1][x+2] = std::max(frameColors[y+1][x+2], 50);
        }
        if(y+2 < MAIN_MAP_HEIGHT){
            frameColors[y+2][x] = std::max(frameColors[y+2][x], 50);
            frameColors[y+2][x+1] = std::max(frameColors[y+2][x+1], 50);
        }
        break;
    
    default:
        break;
    }
}

ScreenFrameName MapFrame::countScreenFrame(int x, int y, playerRotation rotation){
    char cc = mapContent[y][x];
    char cells[8] = {
        mapContent[y][x+1],
        mapContent[y-1][x+1],
        mapContent[y-1][x],
        mapContent[y-1][x-1],
        mapContent[y][x-1],
        mapContent[y+1][x-1],
        mapContent[y+1][x],
        mapContent[y+1][x+1]
    };
    if(cells[(static_cast<int>(rotation)+8)%8] == '?') return snDoor;
    if(!isEmpty(cc)){
        switch (cc)
        {
        case '?':
            return snDoor;
        case 'e':
            return snElevator;
        case '=':
            return snStairs;
        case '~':
            return snLab;
        case '`':
            return snRoom1;
        case '\'':
            return snRoom2;
        case '.':
            return snRoomCommon;
        case ',':
            return snWC; 
        default:
            return snHall;
        }
    }

    if(isWallOrDoor(cells[(static_cast<int>(rotation)+8)%8])){ // спереди стена
        if(isWallOrDoor(cells[(static_cast<int>(rotation)+8+4)%8])) return snStraight;
    }
    else{ //спереди нет стены
        if(isWallOrDoor(cells[(static_cast<int>(rotation)+8+2)%8]) //справа и слева стены
            && isWallOrDoor(cells[(static_cast<int>(rotation)+8-2)%8])){
            
            if(isWallOrDoor(cells[(static_cast<int>(rotation)+8+1)%8]) //спереди по диагонали стены
                || isWallOrDoor(cells[(static_cast<int>(rotation)+8-1)%8]))
                return snStraight;
        }

        if(isWallOrDoor(cells[(static_cast<int>(rotation)+8+2)%8]) ||
            isWallOrDoor(cells[(static_cast<int>(rotation)+8-2)%8])){ //стена только справа или только слева
                if(isWallOrDoor(cells[(static_cast<int>(rotation)+8+1)%8]) // есть все диагональные клетки
                && isWallOrDoor(cells[(static_cast<int>(rotation)+8+3)%8])
                && isWallOrDoor(cells[(static_cast<int>(rotation)+8+5)%8])
                && isWallOrDoor(cells[(static_cast<int>(rotation)+8+7)%8])){
                    if(isWallOrDoor(cells[(static_cast<int>(rotation)+8+4)%8])){ //сзади есть стена
                        if(isWallOrDoor(cells[(static_cast<int>(rotation)+8+2)%8])) // стена именно справа
                            return snLeft;
                        if(isWallOrDoor(cells[(static_cast<int>(rotation)+8-2)%8])) // стена именно слева
                            return snRight;
                    }
                    else { //сзади нет стены
                        return snTurn;
                    }
                }
            }
        return snHall;
    }
    return snHall;
}

bool MapFrame::checkFloorNumberKnowledge(int x, int y, playerRotation rotation){
    char cc = mapContent[y][x];
    char cells[8] = {
        mapContent[y][x+1],
        mapContent[y-1][x+1],
        mapContent[y-1][x],
        mapContent[y-1][x-1],
        mapContent[y][x-1],
        mapContent[y+1][x-1],
        mapContent[y+1][x],
        mapContent[y+1][x+1]
    };
    if(isKeyRoom(cc)) return true;
    if(isWall(cells[(static_cast<int>(rotation)+8)%8]) && isEmpty(cc)
        && ((static_cast<int>(rotation)+8)%8)%2 == 0) return true;
    return false;
}

bool MapFrame::isEmpty(char c){
    return c == ' ';
}
bool MapFrame::isExit(char c){
    return c == '0';
}
bool MapFrame::isClear(char c){
    return c == ' ' || c == '=' || c == 'e' || c == '?' || c == '.' 
        || c == ',' || c == '`' || c == '\'' || c == '~' || c == '0';
}
bool MapFrame::isPassage(char c){
    return c == ' ' || c == '?';
}
bool MapFrame::isFloorChange(char c){
    return c == '=' || c == 'e';
}
bool MapFrame::isKeyRoom(char c){
    return c == '`' || c =='\'' || c == '~';
}
bool MapFrame::isWall(char c){
    return c == '#' || c == '|' || c == '\\' || c == '/' || c == '-' || c == '_' || c == '+';
}
bool MapFrame::isWallOrDoor(char c){
    return isWall(c) || c == '?';
}