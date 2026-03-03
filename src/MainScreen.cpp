    #include "MainScreen.h"

MainScreen::MainScreen(int *floorNumberP, ScreenFrameName *currentFrameNameP, bool *isFloorKnownP){
    floorNumber = floorNumberP;
    currentFrameName = currentFrameNameP;
    isFloorKnown = isFloorKnownP;
    loadFrames();
}

void MainScreen::init(SDL_Renderer *rendererP){
    renderer = rendererP;
}

void MainScreen::loadFrames(){
    try{
        for(int i=0; i < SCREEN_FRAMES_COUNT; ++i){
            std::ifstream frameFile("assets/screenFramesContent/" + std::to_string(i) + ".txt");
            std::string frameString;
            char c;
            int currentRow = 0; 
            char *content[MAIN_SCREEN_HEIGHT];
            while (frameFile.get(c)){
                if(c == '\n'){
                    content[currentRow] = new char[MAIN_SCREEN_WIDTH];
                    strcpy(content[currentRow], frameString.c_str());
                    ++currentRow;
                    frameString = "";
                }
                else
                    frameString += c;

            }
            frames[i].setContent(content);
            frameFile.close();
        }
    }
    catch (std::exception e){
        std::cout<<e.what()<<'\n';
    }
}

void MainScreen::draw(){
    frames[static_cast<int>(*currentFrameName)].draw(renderer);
}

void MainScreen::changeColor(){
    if(*isFloorKnown)
        frames[static_cast<int>(*currentFrameName)].setColorNumber(*floorNumber);
    else
        frames[static_cast<int>(*currentFrameName)].setColorNumber(-1);

}