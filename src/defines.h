#pragma once
#define WINDOW_NAME "Alien State University of People and Stuff"

#define MAIN_SCREEN_WIDTH 128
#define MAIN_SCREEN_HEIGHT 72
#define SCREEN_POS_X 72
#define SCREEN_POS_Y 432
#define SCREEN_FRAMES_COUNT 13

#define END_SCREEN_WIDTH 256
#define END_SCREEN_HEIGHT 106

#define HELP_SCREEN_WIDTH_P 960
#define HELP_SCREEN_HEIGHT_P 540

enum ScreenFrameName{
    snStraight,
    snDoor,
    snTurn,
    snRight,
    snLeft,
    snElevator,
    snStairs,
    snLab,
    snRoom1,
    snRoom2,
    snHall,
    snRoomCommon,
    snWC
};

#define MAIN_MAP_WIDTH 80
#define MAIN_MAP_HEIGHT 45
#define MAP_POS_X 1168
#define MAP_POS_Y 72

#define TIPS_WINDOW_WIDTH MAIN_SCREEN_WIDTH
#define TIPS_WINDOW_HEIGHT 36
#define TIPS_WINDOW_POS_X 72
#define TIPS_WINDOW_POS_Y 72
#define TIP_MAX_WIDTH 32

#define PLAYER_STATE_WIDTH 80
#define PLAYER_STATE_HEIGHT 63
#define PLAYER_STATE_POS_X 1168
#define PLAYER_STATE_POS_Y 504
#define ARROW_SIZE 5
#define ARROW_SHOWN_SIZE 20

#define MAIN_BASIC_WIDTH 1920
#define MAIN_BASIC_HEIGHT 1080

#define WHITE_STRUCT {255, 255, 255, 255}
#define RED_STRUCT {255, 0, 127, 255}
#define GREY_STRUCT {190, 190, 230, 255}
#define BLACK_STRUCT {90, 10, 100, 255}
#define GREEN_STRUCT {0, 255, 127, 255}

#define COLOR_PHASE 0.05

#define GSF_CAN_MOVE    0x0001
#define GSF_CAN_ROTATE  0x0002
#define GSF_CAN_GO_UP   0x0004
#define GSF_CAN_GO_DOWN 0x0008
#define GSF_CAN_EXIT    0x0010

#define SCREEN_FRAME_CONTENT char *content[MAIN_SCREEN_HEIGHT]
#define MAP_FRAME_CONTENT char *content[MAIN_MAP_HEIGHT]

#define FLOORS_NUMBER 4

enum playerRotation{
    rotationR,
    rotationUR,
    rotationU,
    rotationUL,
    rotationL,
    rotationDL,
    rotationD,
    rotationDR,
};