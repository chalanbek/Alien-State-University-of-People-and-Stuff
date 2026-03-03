#pragma once
#include <SDL3/SDL.h>

struct SpawnTemplate
{
    int floorNumber;
    int x;
    int y;
};

class SpawnTemplates
{
public:
    static void chooseTemplate(int *floorNumber, int *x, int *y);
private:
    static const int templatesNum = 20;
    inline static SpawnTemplate templates[templatesNum] = {
        {0, 1, 1},
        {0, 32, 4},
        {0, 73, 12},
        {0, 58, 36},
        {0, 77, 2},
        {1, 1, 1},
        {1, 65, 7},
        {1, 32, 29},
        {1, 71, 32},
        {1, 47, 42},
        {2, 1, 1},
        {2, 66, 39},
        {2, 74, 4},
        {2, 59, 21},
        {2, 9, 43},
        {3, 1, 1},
        {3, 53, 34},
        {3, 12, 39},
        {3, 21, 21},
        {3, 75, 13},
    };
};